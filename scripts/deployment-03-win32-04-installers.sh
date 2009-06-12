#!/bin/bash

if [ ! -d ../dist ]
then
 exit 1
fi

SCRIPTFOLDER=$(pwd)

VERSION=$(./get-version.sh)

cd ../dist

makensis qwatch.nsi
makensis iswatch.nsi

rm *.nsi *.TXT *.bmp *.ico
