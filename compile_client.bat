@echo off

cd client
Codeblocks /na /nd /ns --build HCC.cbp --target="Win32 Release" > ..\Build\compile.log
