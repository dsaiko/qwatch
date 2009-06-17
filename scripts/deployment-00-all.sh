#!/bin/bash

./deployment-01-svn-trunk-source.sh
#./deployment-02-linux-build.sh
./deployment-03-win32-01-prepare.sh
./deployment-03-win32-02-01-build-win32.sh
./deployment-03-win32-02-02-build-win64.sh
./deployment-03-win32-03-postbuild.sh
./deployment-03-win32-04-installers.sh
./deployment-03-win32-05-pack.sh
./deployment-03-win32-06-sign.sh
./deployment-04-dist-files.sh
 