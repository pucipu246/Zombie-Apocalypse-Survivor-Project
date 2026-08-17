@echo off
chcp 65001 > nul
echo ============================
echo    Zombie Survival Game
echo ============================
echo.

REM Kiem tra g++ co chua
where g++ > nul 2>&1
if %errorlevel% neq 0 (
    echo [LOI] Khong tim thay g++.
    echo Vui long cai MinGW va them vao PATH truoc.
    echo Huong dan: https://www.mingw-w64.org/
    echo.
    pause
    exit /b 1
)

echo [1/2] Dang bien dich...
g++ -std=c++17 -Ilib -Iapp app/Game.cpp app/main.cpp -o game.exe
if %errorlevel% neq 0 (
    echo.
    echo [LOI] Bien dich that bai.
    pause
    exit /b 1
)

echo [2/2] Bien dich thanh cong! Dang chay game...
echo.
game.exe
pause
