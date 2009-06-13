#!/bin/bash

if [ ! -d /tmp/dist ]
then
 exit 1
fi
SCRIPTFOLDER=$(pwd)
VERSION=$(./get-version.sh)
cd /tmp/dist

mv iswatch.exe iswatch-$VERSION.exe
mv qwatch.exe qwatch-$VERSION.exe

upx --lzma -9 iswatch-$VERSION.exe
upx --lzma -9 qwatch-$VERSION.exe
