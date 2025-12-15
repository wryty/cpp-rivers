cmake_minimum_required(VERSION 3.10)
project(RiverManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка компилятора для Windows
if(MSVC)
    add_compile_options(/utf-8)
endif()

# Создание исполняемого файла
add_executable(river_system main.cpp)

# Настройки для отладки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(river_system PRIVATE DEBUG)
    target_compile_options(river_system PRIVATE -g -O0)
else()
    target_compile_options(river_system PRIVATE -O2)
endif()