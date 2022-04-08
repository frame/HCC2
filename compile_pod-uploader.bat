@echo off

cd pod-uploader
SET GOOS=windows
SET GOARCH=386
"C:\Program Files\Go\bin\go" build -o ../build/Release/upload.exe upload.go
