#!/bin/bash

if [ ! -d /tmp/dist ]
then
 exit 1
fi
SCRIPTFOLDER=$(pwd)
VERSION=$(./get-version.sh)

cd /tmp/dist/qwatch-$VERSION
cmd /C win-compile.bat

cd /tmp/dist/iswatch-$VERSION
cmd /C win-compile.bat

cd /tmp/dist
cp iswatch-$VERSION/build/iswatch.exe .
cp qwatch-$VERSION/build/qwatch.exe .
