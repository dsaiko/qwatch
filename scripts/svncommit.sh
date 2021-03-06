#!/bin/bash

cd ..

export EDITOR=/usr/bin/vim

rm build/*
rm build/app/*
rm build/tests/*

status="$(svn status)"


if [ "$status" != "" ]
then
    SOURCEMODIFIED=
    for file in $(svn status | awk '{print $2}')
    do
      sourcefile=$(echo $file | grep "src-")
      if [ "$sourcefile" != "" ]
      then
        SOURCEMODIFIED="true"
      fi
    done
    
    if [ "$SOURCEMODIFIED" ] 
    then
        revision=$(svn info src-app/src/version.h | grep Revision | awk '{print $2}')
        echo "// Rev $revision, " $(date) >> src-app/src/version.h
    fi
    
    for file in $(svn status | grep -v ! | awk '{print $2}')
    do
	svn add $file
	sourcefile=$(echo $file | egrep "\\.(h|cpp|pro|txt)$")
	if [ "$sourcefile" != "" ]
	then
	    svn propset svn:keywords "Id Rev Date" $file
	fi
    done
    for file in $(svn status | grep ! | awk '{print $2}')
    do
	svn delete $file
    done
    svn commit
fi