#!/bin/bash

if [ ! -d /tmp/dist ]
then
 exit 1
fi
SCRIPTFOLDER=$(pwd)
VERSION=$(./get-version.sh)
DATE=$(./get-date.sh)
cd /tmp/dist

. googlevars

echo "UPLOADING qwatch-$VERSION-setup.exe ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Featured,Type-Installer,OpSys-Windows" -s "QWatch - Win32/x64 installer (includes native binaries for WinXP, Vista, Vista x64, Win 7, Win 7 x64) - does NOT require administrator rights." qwatch-$VERSION-setup.exe
echo "UPLOADING iswatch-$VERSION-setup.exe ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Type-Installer,OpSys-Windows" -s "ISWatch (QWatch with Intershop logo) - Win32/x64 installer (includes native binaries for WinXP, Vista, Vista x64, Win 7, Win 7 x64) - does NOT require administrator rights." iswatch-$VERSION-setup.exe

echo "UPLOADING qwatch-latest-setup.exe ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Featured,Type-Installer,OpSys-Windows" -s "QWatch - Win32 installer (for WinXP, Vista, Vista x64, Win 7, Win 7 x64) - does NOT require administrator rights." qwatch-latest-setup.exe
echo "UPLOADING iswatch-latest-setup.exe ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Type-Installer,OpSys-Windows" -s "ISWatch (QWatch with Intershop logo) - Win32 installer (for WinXP, Vista, Vista x64, Win 7, Win 7 x64) - does NOT require administrator rights." iswatch-latest-setup.exe

echo "UPLOADING qwatch-$VERSION.exe ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Featured,Type-Executable,OpSys-Windows" -s "QWatch - Win32 executable (for WinXP, Vista, Vista x64, Win 7, Win 7 x64)." qwatch-$VERSION.exe
echo "UPLOADING iswatch-$VERSION.exe ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Type-Executable,OpSys-Windows" -s "ISWatch (QWatch with Intershop logo) - Win32 executable (for WinXP, Vista, Vista x64, Win 7, Win 7 x64)." iswatch-$VERSION.exe

echo "UPLOADING qwatch-$VERSION.tar.gz ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Featured,Type-Source,OpSys-Windows,OpSys-Linux" -s "QWatch source code and build scripts (QT 4.5 qmake)." qwatch-$VERSION.tar.gz
echo "UPLOADING qwatch-latest.tar.gz ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Featured,Type-Source,OpSys-Windows,OpSys-Linux" -s "QWatch source code and build scripts (QT 4.5 qmake)." qwatch-latest.tar.gz

echo "UPLOADING qwatch-currentversion.xml ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Type-Docs" -s "QWatch - current version information." qwatch-currentversion.xml
echo "UPLOADING iswatch-currentversion.xml ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Type-Docs" -s "ISWatch (QWatch with Intershop logo) - current version information." iswatch-currentversion.xml


echo "UPLOADING changelog.txt ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Type-Docs" -s "Changelog - EN." changelog.txt
echo "UPLOADING changelog-cs.txt ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Type-Docs" -s "Changelog - CS." changelog-cs.txt
echo "UPLOADING changelog-de.txt ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Type-Docs" -s "Changelog - DE." changelog-de.txt

echo "UPLOADING qwatch-$VERSION-x64.exe ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Featured,Type-Executable,OpSys-Windows" -s "QWatch - Windows x64 executable (for Vista x64, Win 7 x64)." qwatch-$VERSION-x64.exe
echo "UPLOADING iswatch-$VERSION-x64.exe ..."
$SCRIPTFOLDER/googlecode_upload.py -p qwatch -u $GOOGLECODE_USER -w $GOOGLECODE_PASSWORD -l "Type-Executable,OpSys-Windows" -s "ISWatch (QWatch with Intershop logo) - Windows x64 executable (for Vista x64, Win 7 x64)." iswatch-$VERSION-x64.exe

