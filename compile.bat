@echo off

cd client
"C:\Program Files\CodeBlocks\Codeblocks.exe" /na /nd /ns --build HCC.cbp --target="Win32 Release" > ..\Build\compile.log

