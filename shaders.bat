@echo off
echo Running
if "%~2"=="" (
    echo Usage: %0 ^<source^> ^<destination^>
    exit /b 1
)

set "source=%~1"
set "destination=%~2"

copy "%source%" "%destination%"

if %errorlevel% neq 0 (
    echo An error occurred while copying the file.
) else (
    echo File copied successfully.
)