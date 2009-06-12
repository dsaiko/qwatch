#!/bin/bash

if [ ! -d ../dist ]
then
 exit 1
fi
 
SCRIPTFOLDER=$(pwd)

VERSION=$(./get-version.sh)

cd ../dist

cmd /C win-compile.bat


