#!/bin/bash

if [ ! -d ../dist ]
then
 exit 1
fi
 
 
SCRIPTFOLDER=$(pwd)

TMPFILE=/tmp/qwatch-$RANDOM-$RANDOM

mkdir $TMPFILE

cd $TMPFILE

cp $SCRIPTFOLDER/../dist/* .

ls *.tar.gz | xargs -l tar xzf

cd iswatch*

qmake 
make
cp build/iswatch $SCRIPTFOLDER/../dist


cd ..
cd qwatch*

qmake
make
cp build/qwatch $SCRIPTFOLDER/../dist
cp build/qwatch-tests $SCRIPTFOLDER/../dist

cd $SCRIPTFOLDER

rm -rf $TMPFILE
