@echo off
setlocal EnableDelayedExpansion

rem Ensure correct argument count
if "%~2"=="" (
    echo Usage: %0 [-c | -w | -l | -s] filename
    exit /b
)

rem Get operation type (-c = count characters, -w = count words, -l = count lines, -s = get size)
set operation=%1
set filename=%2

rem Check if file exists
if not exist "%filename%" (
    echo File "%filename%" does not exist.
    exit /b
)

rem Count characters in file
if "%operation%"=="-c" (
    set /a count=0
    for /f "delims=" %%A in (%filename%) do (
        set line=%%A
        rem Count characters in each line
        set /a count+=0
        for %%B in (!line!) do (
            rem Increase count for every character in the line
            set /a count+=1
        )
    )
    echo Total characters: %count%
)

rem Count words in file
if "%operation%"=="-w" (
    set /a words=0
    for /f %%A in (%filename%) do (
        set line=%%A
        rem Split the line into words and count them
        for %%B in (!line!) do set /a words+=1
    )
    echo Total words: %words%
)

rem Count lines in file
if "%operation%"=="-l" (
    set /a lines=0
    for /f %%A in (%filename%) do (
        rem Increment line count for each line
        set /a lines+=1
    )
    echo Total lines: %lines%
)

rem Get file size in bytes
if "%operation%"=="-s" (
    for %%A in (%filename%) do (
        set size=%%~zA
    )
    echo File size: %size% bytes
)

endlocal
