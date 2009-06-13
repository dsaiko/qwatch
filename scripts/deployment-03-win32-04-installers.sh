#!/bin/bash

if [ ! -d /tmp/dist ]
then
 exit 1
fi
SCRIPTFOLDER=$(pwd)
VERSION=$(./get-version.sh)
cd /tmp/dist

makensis qwatch.nsi
makensis iswatch.nsi

rm *.nsi *.TXT *.bmp *.ico
