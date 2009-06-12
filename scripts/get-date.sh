#!/bin/bash

VERSIONFILE=../src-app/src/version.h

date=$(cat $VERSIONFILE | egrep "(VERSIONDATE)" | awk '{gsub("[^0123456789\\- ]",""); print}')

date=$(echo $date | awk '{print $1}')

echo $date