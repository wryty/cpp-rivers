@echo off
echo Компиляция программы учета рек...

:: Проверяем доступные компиляторы
where cl >nul 2>&1
if %errorlevel% equ 0 (
    echo Используется MSVC компилятор...
    cl /EHsc /std:c++17 /Fe:river_system.exe main.cpp
    if %errorlevel% equ 0 (
        echo Компиляция успешно завершена!
        echo.
        river_system.exe
    ) else (
        echo Ошибка компиляции!
        pause
    )
) else (
    where g++ >nul 2>&1
    if %errorlevel% equ 0 (
        echo Используется G++ компилятор...
        g++ -std=c++17 -o river_system.exe main.cpp
        if %errorlevel% equ 0 (
            echo Компиляция успешно завершена!
            echo.
            river_system.exe
        ) else (
            echo Ошибка компиляции!
            pause
        )
    ) else (
        echo Не найден компилятор C++!
        echo Установите MinGW-w64 или Visual Studio Build Tools
        pause
    )
)