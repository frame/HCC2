@ECHO OFF

REM HCC Public Order Database plugin
REM v1.0 2009-03-16
REM
REM by Arcat, OoR

IF (%1)==() GOTO ERRORHCC
IF (%2)==() GOTO ERRORHCC
IF (%3)==() GOTO ERRORHCC
IF (%4)==() GOTO ERRORHCC
IF NOT %~2==order GOTO ERRORBONUS
IF NOT EXIST "%~1\report.txt" GOTO ERROR
IF NOT EXIST "%~1\report.html" GOTO ERROR
IF NOT EXIST "%~1\report.xml" GOTO ERROR
IF NOT EXIST "%~1\order.xml" GOTO ERROR
IF NOT EXIST "%~1\profile.xml" GOTO PLUGINSTART
SET curl_profile=-F "profile=@%~1\profile.xml"

:PLUGINSTART

SET uid=%random%%random%%random%
curl.exe -F "order=@%~1\order.xml" -F "report=@%~1\report.xml" -F "report_html=@%~1\report.html" %curl_profile% -F "type=%~2" -F "hcc-version=%~3" -F "hcc-database=%~4" -F "name=%~5" -F "shard=%~6" -F "email=%~7" -F "uid=%uid%" http://hcc.reclamation.dk/pod/submit.php
start http://hcc.reclamation.dk/pod/?uid=%uid%
exit

:ERRORBONUS
echo Error - This plugin cannot process Bonus reports.
pause
exit

:ERRORHCC
echo Error - This file can only be launched through HCC.
pause
exit

:ERROR
echo Error - An unexpected issue occured. Please contact plugin developer or HCC support.
pause
exit