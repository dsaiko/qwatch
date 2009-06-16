#!/bin/bash


/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "QWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" qwatch/uninstall.exe
/cygdrive/C/Program\ Files/Microsoft\ SDKs/Windows/v6.1/bin/signtool.exe sign /a /d "ISWatch" /du "http://qwatch.googlecode.com" /t "http://timestamp.comodoca.com/authenticode" iswatch/uninstall.exe
