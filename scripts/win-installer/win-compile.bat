cd iswatch*
call c:\qt\static\bin\qtenv.bat
qmake
mingw32-make
copy build\iswatch.exe ..\
cd ..\

cd qwatch*
call c:\qt\static\bin\qtenv.bat
qmake
mingw32-make
copy build\qwatch.exe ..\
cd ..\
