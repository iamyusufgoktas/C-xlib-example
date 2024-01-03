cmake_minimum_required(VERSION 3.23)
project(autoClicker)

set(CMAKE_C_FLAGS  -lX11 -lXtst)
set(CMAKE_C_STANDARD)

add_executable(autoClicker Introduction.c)

