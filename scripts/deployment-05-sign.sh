#!/bin/bash

if [ ! -d /tmp/dist ]
then
 exit 1
fi
SCRIPTFOLDER=$(pwd)
VERSION=$(./get-version.sh)
cd /tmp/dist


/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "QWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" qwatch-$VERSION.exe
/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "QWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" qwatch-$VERSION-x64.exe
/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "QWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" qwatch-$VERSION-setup.exe
/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "QWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" qwatch-latest-setup.exe

/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "ISWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" iswatch-$VERSION.exe
/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "ISWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" iswatch-$VERSION-x64.exe
/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "ISWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" iswatch-$VERSION-setup.exe
/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "ISWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" iswatch-latest-setup.exe