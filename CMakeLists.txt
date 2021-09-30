cmake_minimum_required(VERSION 3.20)
project(untitled1)


add_subdirectory(tests)
set(CMAKE_CXX_STANDARD 14)

add_executable(untitled1 src/main.cpp src/Game.cpp src/Game.h src/Themes.cpp src/Themes.h)
