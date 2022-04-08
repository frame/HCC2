@echo off

cd pod-uploader
SET GOOS=windows
SET GOARCH=386
go build -o ../build/Release/upload.exe upload.go
