#!/bin/bash

if [ ! -d /tmp/dist ]
then
 exit 1
fi
SCRIPTFOLDER=$(pwd)
VERSION=$(./get-version.sh)
cd /tmp/dist

upx --lzma -9 iswatch.exe
upx --lzma -9 qwatch.exe

mpress -x iswatch-x64.exe
mpress -x qwatch-x64.exe

mv iswatch.exe iswatch-$VERSION.exe
mv qwatch.exe qwatch-$VERSION.exe
mv iswatch-x64.exe iswatch-$VERSION-x64.exe
mv qwatch-x64.exe qwatch-$VERSION-x64.exe
