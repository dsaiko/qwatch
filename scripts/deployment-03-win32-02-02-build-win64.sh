#!/bin/bash

if [ ! -d /tmp/dist ]
then
 exit 1
fi
SCRIPTFOLDER=$(pwd)
VERSION=$(./get-version.sh)

cd /tmp/dist/qwatch-$VERSION-x64
cmd /C win-compile.bat

cd /tmp/dist/iswatch-$VERSION-x64
cmd /C win-compile.bat

cd /tmp/dist
cp iswatch-$VERSION-x64/build/iswatch.exe ./iswatch-x64.exe
cp qwatch-$VERSION-x64/build/qwatch.exe ./qwatch-x64.exe
