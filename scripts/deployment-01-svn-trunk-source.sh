#!/bin/bash

SCRIPTFOLDER=$(pwd)

TMPFILE=/tmp/qwatch-$RANDOM-$RANDOM
svn export http://qwatch.googlecode.com/svn/trunk/ $TMPFILE

if [ ! -d $TMPFILE ]
then
 exit 1
fi

cd $TMPFILE
find . | grep Makefile | xargs -l rm
find . | grep \\.user | xargs -l rm


cd scripts
VERSION=$(./get-version.sh)

cd ..
mkdir qwatch-$VERSION
mv * qwatch-$VERSION/

tar czf qwatch-$VERSION.tar.gz qwatch-$VERSION

mv qwatch-$VERSION iswatch-$VERSION
cd iswatch-$VERSION
cd src-app
mv src-app.pro src-app.pro.org
cat src-app.pro.org | awk '{gsub("#ISBUILD","");print}' > src-app.pro
rm src-app.pro.org
cd ..
cd ..
tar czf iswatch-$VERSION.tar.gz iswatch-$VERSION


cd $SCRIPTFOLDER
rm -rf /tmp/dist
mkdir /tmp/dist
cd /tmp/dist

cp $TMPFILE/qwatch-$VERSION.tar.gz .
cp $TMPFILE/iswatch-$VERSION.tar.gz .

rm -rf $TMPFILE