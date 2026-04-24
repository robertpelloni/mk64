@echo off
setlocal
title MK64 (make build)
cd /d "%~dp0"

echo [MK64 (make build)] Starting...
where make >nul 2>nul
if errorlevel 1 (
    echo [MK64 (make build)] make not found. Please install it.
    pause
    exit /b 1
)

make

if errorlevel 1 (
    echo [MK64 (make build)] Exited with error code %errorlevel%.
    pause
)
endlocal
