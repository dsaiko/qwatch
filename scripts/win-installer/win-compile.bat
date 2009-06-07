cd iswatch-__VERSION__
call c:\qt\static\bin\qtenv.bat
qmake
mingw32-make
copy build\iswatch.exe ..\
cd ..\

cd qwatch-__VERSION__
call c:\qt\static\bin\qtenv.bat
qmake
mingw32-make
copy build\qwatch.exe ..\
cd ..\
