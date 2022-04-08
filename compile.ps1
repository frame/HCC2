Param(
    [Parameter(Mandatory=$true)]
    [ValidateSet('all', 'database', 'pod-uploader', 'client', 'installer')]
    [string[]]
    $task
)

$continue = $true
$scriptFolder = Split-Path -Parent $MyInvocation.MyCommand.Path
cd -Path $scriptFolder

$error.clear()

if ($continue -eq $true -and ($task -eq 'database' -or $task -eq 'all')) {
    Write-Host "database"
    Compress-Archive -Path database\* -Force -DestinationPath build\database.zip
    if ($error[0] -ne $null) {
        $continue = $false;
        Write-Host "ERROR"
    } else {
        Write-Host "OK`n" -ForegroundColor Green
    }
}
if ($continue -eq $true -and ($task -eq 'pod-uploader' -or $task -eq 'all')) {
    Write-Host "pod-uploader"
    cd -Path "pod-uploader"
    $env:GOOS = "windows"
    $env:GOARCH = "386"
    go build -o "$($scriptFolder + "\build\Release\upload.exe")" upload.go
    if ($LASTEXITCODE -ne 0 ) {
        $continue = $false;
        Write-Host "ERROR"
    } else {
        Write-Host "OK`n" -ForegroundColor Green
    }
    cd -Path $scriptFolder
}
if ($continue -eq $true -and ($task -eq 'client' -or $task -eq 'all')) {
    Write-Host "client"
    cd -Path "client"
    Codeblocks /na /nd /ns --build HCC.cbp --target="Win32 Release" > "$($scriptFolder + "\Build\compile.log")"
    if ($LASTEXITCODE -ne 0 ) {
        $continue = $false;
        Write-Host "ERROR"
    } else {
        Write-Host "OK`n" -ForegroundColor Green
    }
    cd -Path $scriptFolder
}
if ($continue -eq $true -and ($task -eq 'installer' -or $task -eq 'all')) {
    Write-Host "installer"
    cd -Path "installer\nsis"
    makensis /V2 HCC_installer.nsi
    if ($LASTEXITCODE -ne 0 ) {
        $continue = $false;
        Write-Host "ERROR"
    } else {
        Write-Host "OK`n" -ForegroundColor Green
    }
    cd -Path $scriptFolder
}