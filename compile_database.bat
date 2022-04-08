@echo off

PowerShell -NoProfile -ExecutionPolicy Bypass -Command "Compress-Archive -Path database\* -Force -DestinationPath build\database.zip"
