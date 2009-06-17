#!/bin/bash

if [ ! -d /tmp/dist ]
then
 exit 1
fi
SCRIPTFOLDER=$(pwd)
VERSION=$(./get-version.sh)
DATE=$(./get-date.sh)
cd /tmp/dist

rm *.md5 *.xml

for f in *
do
 md5sum $f > $f.md5
done

FILE=qwatch-$VERSION-setup.exe
MD5=$(cat $FILE.md5 | awk '{print $1}')
SIZE=$(ls -la $FILE | awk '{print $5}')

cat $SCRIPTFOLDER/win-installer/currentversion.xml | sed "s/__VERSION__/$VERSION/" | sed "s/__DATE__/$DATE/" | sed "s/__FILE__/$FILE/" | sed "s/__MD5__/$MD5/" | sed "s/__SIZE__/$SIZE/" > qwatch-currentversion.xml

FILE=iswatch-$VERSION-setup.exe
MD5=$(cat $FILE.md5 | awk '{print $1}')
SIZE=$(ls -la $FILE | awk '{print $5}')

cat $SCRIPTFOLDER/win-installer/currentversion.xml | sed "s/__VERSION__/$VERSION/" | sed "s/__DATE__/$DATE/" | sed "s/__FILE__/$FILE/" | sed "s/__MD5__/$MD5/" | sed "s/__SIZE__/$SIZE/" > iswatch-currentversion.xml

rm *.md5

cp $SCRIPTFOLDER/../CHANGELOG.TXT changelog.txt
cp $SCRIPTFOLDER/../CHANGELOG-DE.TXT changelog-de.txt
cp $SCRIPTFOLDER/../CHANGELOG-CS.TXT changelog-cs.txt

chmod 777 *
