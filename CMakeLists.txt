cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем директорию с заголовками
include_directories(MySTL/include)

# Добавляем исполняемый файл и указываем исходники
add_executable(MyProject MySTL/src/Main.cpp)
