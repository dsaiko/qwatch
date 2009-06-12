#!/bin/bash

if [ ! -d ../dist ]
then
 exit 1
fi

SCRIPTFOLDER=$(pwd)

VERSION=$(./get-version.sh)

cd ../dist

find . -type d | grep $VERSION | xargs -l rm -rf

tar xzf iswatch*.tar.gz
tar xzf qwatch*.tar.gz

cat $SCRIPTFOLDER/win-installer/win-compile.bat | sed "s/__VERSION__/$VERSION/" > win-compile.bat

