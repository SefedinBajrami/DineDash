@echo off
REM OpenGL Car Simulator Build Script for Windows

echo ======================================
echo OpenGL Car Simulator - Build Script
echo ======================================
echo.

REM Check if CMake is installed
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Error: CMake is not installed
    echo Please install CMake from https://cmake.org/download/
    pause
    exit /b 1
)

REM Display CMake version
echo CMake found:
cmake --version | findstr /C:"cmake version"
echo.

REM Create build directory
echo Creating build directory...
if not exist build mkdir build
cd build

REM Run CMake
echo.
echo Running CMake...
cmake .. -G "Visual Studio 16 2019" -A x64
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed
    pause
    exit /b 1
)

REM Build the project
echo.
echo Building project...
cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo Build failed
    pause
    exit /b 1
)

echo.
echo ======================================
echo Build successful!
echo ======================================
echo.
echo To run the simulator:
echo   cd build\Release
echo   CarSimulator.exe
echo.
pause
