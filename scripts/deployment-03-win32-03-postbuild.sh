#!/bin/bash

if [ ! -d /tmp/dist ]
then
 exit 1
fi
SCRIPTFOLDER=$(pwd)
VERSION=$(./get-version.sh)
cd /tmp/dist

find . -type d | grep -v "\\.$" |  xargs -l rm -rf
rm -f *.nsi *.TXT *.bmp *.ico

cat $SCRIPTFOLDER/win-installer/installer.nsi | sed "s/__VERSION__/$VERSION/" | sed "s/__APPFILE__/qwatch/" | sed "s/__APPNAME__/QWatch/" > qwatch.nsi
cat $SCRIPTFOLDER/win-installer/installer.nsi | sed "s/__VERSION__/$VERSION/" | sed "s/__APPFILE__/iswatch/" | sed "s/__APPNAME__/ISWatch/" > iswatch.nsi

cp $SCRIPTFOLDER/win-installer/res/* .

cd /tmp/dist
mkdir x86
mkdir x64

cp qwatch.exe x86/
cp iswatch.exe x86/
cp iswatch-x64.exe x64/iswatch.exe
cp qwatch-x64.exe x64/qwatch.exe


/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "QWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" x86/qwatch.exe
/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "ISWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" x86/iswatch.exe
/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "QWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" x64/qwatch.exe
/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "ISWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" x64/iswatch.exe

mkdir qwatch
mkdir iswatch
cp $SCRIPTFOLDER/win-installer/qwatch/uninstall.exe qwatch/
cp $SCRIPTFOLDER/win-installer/iswatch/uninstall.exe iswatch/