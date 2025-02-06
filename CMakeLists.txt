cmake_minimum_required(VERSION 3.22.1)
project(Esolang)  # プロジェクト名

set(CMAKE_CXX_STANDARD 17)  # C++17

add_executable(brainfuck brainfuck.cpp)
add_executable(cow cow.cpp)