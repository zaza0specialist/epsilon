@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=amd64 >nul 2>&1
cd /d "J:\Epsilon project\epsilon\build"
cmake -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
if %errorlevel% neq 0 exit /b %errorlevel%
ninja
