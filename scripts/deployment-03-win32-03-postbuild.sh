#!/bin/bash

if [ ! -d ../dist ]
then
 exit 1
fi

SCRIPTFOLDER=$(pwd)

VERSION=$(./get-version.sh)

cd ../dist

find . -type d | grep $VERSION | xargs -l rm -rf

rm *.bat

cat $SCRIPTFOLDER/win-installer/installer.nsi | sed "s/__VERSION__/$VERSION/" | sed "s/__APPFILE__/qwatch/" | sed "s/__APPNAME__/QWatch/" > qwatch.nsi
cat $SCRIPTFOLDER/win-installer/installer.nsi | sed "s/__VERSION__/$VERSION/" | sed "s/__APPFILE__/iswatch/" | sed "s/__APPNAME__/ISWatch/" > iswatch.nsi

cp $SCRIPTFOLDER/win-installer/res/* .

chmod 777 *



