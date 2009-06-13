#!/bin/bash

if [ ! -d /tmp/dist ]
then
 exit 1
fi
SCRIPTFOLDER=$(pwd)
VERSION=$(./get-version.sh)
cd /tmp/dist

find . -type d | grep $VERSION | xargs -l rm -rf

tar xzf iswatch-$VERSION.tar.gz
tar xzf qwatch-$VERSION.tar.gz

cp -r iswatch-$VERSION iswatch-$VERSION-x64
cp -r qwatch-$VERSION qwatch-$VERSION-x64

cat $SCRIPTFOLDER/win-installer/win-compile.bat | sed "s/__ARCH__/x86/" > iswatch-$VERSION/win-compile.bat
cat $SCRIPTFOLDER/win-installer/win-compile.bat | sed "s/__ARCH__/x86/" > qwatch-$VERSION/win-compile.bat
cat $SCRIPTFOLDER/win-installer/win-compile.bat | sed "s/__ARCH__/x64/" > iswatch-$VERSION-x64/win-compile.bat
cat $SCRIPTFOLDER/win-installer/win-compile.bat | sed "s/__ARCH__/x64/" > qwatch-$VERSION-x64/win-compile.bat

cp $SCRIPTFOLDER/win-installer/msvc-qt.cmd iswatch-$VERSION/
cp $SCRIPTFOLDER/win-installer/msvc-qt.cmd qwatch-$VERSION/
cp $SCRIPTFOLDER/win-installer/msvc-qt.cmd iswatch-$VERSION-x64/
cp $SCRIPTFOLDER/win-installer/msvc-qt.cmd qwatch-$VERSION-x64/
