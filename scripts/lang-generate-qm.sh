#!/bin/bash

cd ../src-app

/cygdrive/c/Qt/dynamic/qt/bin/lrelease -verbose src-app.pro

mv ../lang/*.qm ../src-app/res/translations/