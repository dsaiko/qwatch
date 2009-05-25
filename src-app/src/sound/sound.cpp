/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2009 Dusan Saiko dusan.saiko@gmail.com
 *
 * $Rev: 45 $
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Sound provider
 */


#include "sound/sound.h"

#ifdef Q_OS_WIN
#include "qt_windows.h"
#endif
#ifdef Q_OS_LINUX
#include <alsa/asoundlib.h>
#endif

#include <QFile>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QSound>
#include <QTimer>
#include <QFile>
#include <QThread>
#include <QObject>
#include <QPointer>


#if WORDS_BIGENDIAN
#define SwapLE16(x) ((((u_int16_t)x)<<8)|(((u_int16_t)x)>>8))
#define SwapLE32(x) ((((u_int32_t)x)<<24)|((((u_int32_t)x)<<8)&0x00FF0000) \
                     |((((u_int32_t)x)>>8)&0x0000FF00)|(((u_int32_t)x)>>24))
#else
#define SwapLE16(x) (x)
#define SwapLE32(x) (x)
#endif

#define BUFFERSIZE 2048
#define DEVICE "default"

typedef struct
{       quint32      size ;
        quint16      formatTag ;
        quint16      channels ;
        quint32      samplesPerSec ;
        quint32      avgBytesPerSec ;
        quint16      blockAlign ;
        quint16      bitsPerSample ;
} SOUNDWAVEFORMAT;

class QSound2
{
public:
        QSound2(const QString wavFile);
        ~QSound2();

        bool isAvailable() { return available; }
        void play();

private:
        bool initialise() ;
        SOUNDWAVEFORMAT waveformat;

        QFile *soundFile;
        bool available;
        int  dataStart;
};

#ifdef Q_OS_WIN
class QSound2Win
{

public:
        virtual ~QSound2Win(void);

public:
        bool play(int channels, int sampleRate, int bitsPerSample, QByteArray data);
private:
        void close();
        bool static CALLBACK waveOut_Proc(HWAVEOUT hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

private:
        QByteArray data;
        bool finished;
        HWAVEOUT m_hWaveout;
        WAVEHDR m_WaveHeader;
};
#endif

#ifdef Q_OS_LINUX
class QSound2Linux
{
public:
        bool play(QFile *soundFile, SOUNDWAVEFORMAT &waveformat, int dataStart);
};
#endif

QSound2::QSound2(const QString wavFile)
{
        soundFile = new QFile(wavFile);
        available = initialise();
}

QSound2::~QSound2()
{
//    qDebug() << "QSound2 destructor";
    soundFile->close();
    delete soundFile;    
}

bool QSound2::initialise()
{
    if(soundFile->exists() == false) {
        return false;
    }

    if (soundFile->open(QIODevice::ReadOnly) == false) {
     return false;
    }

    if ( soundFile->seek(0) == false) {
        return false;
    }

    QByteArray buffer = soundFile->read(BUFFERSIZE);

    if (buffer.indexOf("RIFF") != 0) {
         qDebug() << "Invalid data format (RIFF):" << soundFile;
         return  false;
    }

    if (buffer.indexOf("WAVE") == -1) {
        qDebug() << "Invalid data format (WAVE):" << soundFile;
        return false;
    }

    int pos = buffer.indexOf("fmt");
    if (pos == -1) {
        qDebug() << "Invalid data format (fmt):" << soundFile;
        return false;
    }

    pos += 4;

    memcpy (&waveformat, (buffer.constData()+pos), sizeof (SOUNDWAVEFORMAT)) ;
    waveformat.size = SwapLE32(waveformat.size);
    waveformat.formatTag = SwapLE16(waveformat.formatTag) ;
    waveformat.channels = SwapLE16(waveformat.channels) ;
    waveformat.samplesPerSec = SwapLE32(waveformat.samplesPerSec) ;
    waveformat.avgBytesPerSec = SwapLE32(waveformat.avgBytesPerSec) ;
    waveformat.blockAlign = SwapLE16(waveformat.blockAlign) ;
    waveformat.bitsPerSample = SwapLE16(waveformat.bitsPerSample) ;

    pos = buffer.indexOf("data");
    if (pos == -1) {
        qDebug() << "Invalid data format (data):" << soundFile;
        return false;
    }

    dataStart = pos + 8;
    return true ;
}


void QSound2::play()
{
    if (available == false) {
            return;
    }

    #ifdef Q_OS_LINUX
        QSound2Linux soundLinux;
        soundLinux.play(soundFile, waveformat, dataStart);
    #endif

    #ifdef Q_OS_WIN
    soundFile->seek(dataStart);

    QSound2Win soundWin;
    soundWin.play(waveformat.channels, waveformat.samplesPerSec, waveformat.bitsPerSample, soundFile->readAll());
    #endif
}

#ifdef Q_OS_WIN
QSound2Win::~QSound2Win(void)
{
//        qDebug() << "QSound2Win destructor";
        // Close output device
        close();
}

void QSound2Win::close()
{

        if (waveOutReset(m_hWaveout) == MMSYSERR_NOERROR) {
               waveOutUnprepareHeader(m_hWaveout, &m_WaveHeader, sizeof(WAVEHDR));
        }

        // Close output device
        waveOutClose(m_hWaveout);
        m_hWaveout = NULL;
        finished = true;
}

bool QSound2Win::play(int channels, int sampleRate, int bitsPerSample, QByteArray soundData)
{
    // Init members
    m_hWaveout = NULL;
    memset(&m_WaveHeader, 0, sizeof(WAVEHDR));
    finished = false;

    // Open output device
    SHORT format = WAVE_FORMAT_PCM;
    SHORT blockAlign = channels << 1;
    WAVEFORMATEX wfex;
    wfex.wFormatTag = format;
    wfex.nChannels = channels;
    wfex.nSamplesPerSec = sampleRate;
    wfex.nAvgBytesPerSec = blockAlign * sampleRate;
    wfex.nBlockAlign = blockAlign;
    wfex.wBitsPerSample = bitsPerSample;
    wfex.cbSize = 0;
    if (waveOutOpen(&m_hWaveout, WAVE_MAPPER, &wfex, (DWORD_PTR)&QSound2Win::waveOut_Proc, (DWORD)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
    {
            m_hWaveout = NULL;
            return false;
    }

    data = soundData;

    // Start playback
    m_WaveHeader.lpData = (LPSTR)data.data();
    m_WaveHeader.dwBufferLength = data.size();
    if (waveOutPrepareHeader(m_hWaveout, &m_WaveHeader, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        return false;
    } else {
        if (waveOutWrite(m_hWaveout, &m_WaveHeader, sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
            return false;
    }

    while(finished == false) {
        _sleep(100);
    }
    return true;
}

bool QSound2Win::waveOut_Proc(HWAVEOUT hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
        bool bResult = true;

        // Get current object
        QSound2Win* pWave = (QSound2Win*)dwInstance;

        if (uMsg == WOM_DONE) {
            if (waveOutUnprepareHeader(pWave->m_hWaveout, &pWave->m_WaveHeader, sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
                    bResult = FALSE;
            pWave->finished=true;
        }

        return bResult;
}
#endif


#ifdef Q_OS_LINUX
bool QSound2Linux::play(QFile *soundFile, SOUNDWAVEFORMAT &waveformat, int dataStart)
{
    snd_pcm_format_t format;

    switch (waveformat.bitsPerSample)
    {
                case 8:
                        format = SND_PCM_FORMAT_U8 ;
                        break;
                case 16:
                        format = SND_PCM_FORMAT_S16_LE ;
                        break;
                case 32 :
                        format = SND_PCM_FORMAT_S32_LE;
                        break;
                default :
                        qDebug() << "Bad format - bits per seconds:" << waveformat.bitsPerSample;
                        return  FALSE ;
                        break;
    }

    snd_pcm_t *handle;
    snd_pcm_uframes_t bufferSize;

    snd_pcm_hw_params_t *params;
    int err;

    snd_pcm_hw_params_alloca(&params);

    if ((err = snd_pcm_open (&handle, DEVICE, SND_PCM_STREAM_PLAYBACK,SND_PCM_ASYNC)) < 0) {
        qDebug() << "Cannot open" << DEVICE << "audio device:" << snd_strerror (err);
        return false;
    }

    if ((err = snd_pcm_nonblock(handle, 1))< 0) {
        qDebug() << "Nonblock error:" << snd_strerror(err);
        return false;
    }

    if ((err = snd_pcm_hw_params_any(handle, params)) < 0)
    {
        qDebug() << "Can not configure PCM device" << DEVICE << ":" << snd_strerror(err);
        return false;
    }

    if((err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
            qDebug() << "Error setting access to device " << DEVICE << ":" << snd_strerror(err);
            return false;
    }

    if((err = snd_pcm_hw_params_set_format(handle, params, format)) <0)
    {
            qDebug() << "Sample format not available for " << soundFile << ":" << snd_strerror(err);
            return false;
    }

    if((err = snd_pcm_hw_params_set_channels(handle, params, waveformat.channels)) < 0)
    {
        qDebug() << "Channels not available " << soundFile << ":" << snd_strerror(err);
        return false;
    }

    if((err = snd_pcm_hw_params_set_rate_near(handle, params, &waveformat.samplesPerSec, 0)) < 0)
    {
        qDebug() << "Sample rate not available " << soundFile << ":" << snd_strerror(err);
        return false;
    }

    if((err = snd_pcm_hw_params(handle, params)) <0)
    {
        qDebug() << "Unable to set hw params " << soundFile << ":" << snd_strerror(err);
        return false;
    }

    snd_pcm_uframes_t chunkSize = 0;
    bufferSize=0;
    snd_pcm_hw_params_get_buffer_size(params, &bufferSize);
    snd_pcm_hw_params_get_period_size(params, &chunkSize, 0);
    int bitsPerFrame = snd_pcm_format_physical_width(format) * waveformat.channels;

    soundFile->seek(dataStart);

    do {
        QByteArray data = soundFile->read(bufferSize);
        if(data.length() == 0) break;
        snd_pcm_writei(handle, data.constData(), data.length()*8/bitsPerFrame);
    } while(true);

    snd_pcm_drain(handle);

    return true;
}
#endif

WavSound::WavSound(const QString wavFile) {
    this->wavFile = wavFile;
    connect(this,SIGNAL(finished()),this,SLOT(deleteLater()));
}

WavSound::~WavSound() {
//    qDebug() << "WavSound destructor";
}

void WavSound::run() {
    QSound2 snd(wavFile);
    snd.play();
}

void WavSound::playWav(const QString wavResource)
{
    WavSound *thread = new WavSound(wavResource);
    thread->start();
}










