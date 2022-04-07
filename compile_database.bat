@echo off

PowerShell -NoProfile -ExecutionPolicy Bypass -Command "Compress-Archive -Path database\* -DestinationPath build\database.zip"
