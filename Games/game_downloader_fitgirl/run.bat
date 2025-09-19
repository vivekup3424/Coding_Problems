@echo off
echo ====================================
echo  FitGirl Game Downloader - AUTO MODE
echo ====================================
echo.

REM Check if virtual environment exists
if not exist "venv" (
    echo Creating virtual environment...
    python -m venv venv
    if %errorlevel% neq 0 (
        echo ERROR: Failed to create virtual environment
        echo Make sure Python is installed and in your PATH
        pause
        exit /b 1
    )
)

REM Activate virtual environment
echo Activating virtual environment...
call venv\Scripts\activate.bat
if %errorlevel% neq 0 (
    echo ERROR: Failed to activate virtual environment
    pause
    exit /b 1
)

REM Install dependencies if needed
if not exist "venv\Lib\site-packages\selenium" (
    echo Installing dependencies...
    pip install -r requirements.txt
    if %errorlevel% neq 0 (
        echo ERROR: Failed to install dependencies
        pause
        exit /b 1
    )
)

REM Run the automated downloader
echo.
echo Starting Automated FitGirl Game Downloader...
echo This will run without asking for input.
echo Press Ctrl+C to stop at any time.
echo.
python fitgirl_downloader.py

echo.
echo Downloads finished!
pause