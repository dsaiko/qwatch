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
