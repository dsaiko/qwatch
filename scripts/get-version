#!/bin/bash

VERSIONFILE=../src-app/src/version.h

version=$(cat $VERSIONFILE | egrep "(MAJORVERSION|MINORVERSION)" | awk '{gsub("[^0123456789\\.]",""); print}')

version=$(echo $version | sed "s/ //")

echo $version