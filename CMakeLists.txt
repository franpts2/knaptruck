add_compile_definitions()
cmake_minimum_required(VERSION 3.30)
project(DA2425_PROJ2)

set(CMAKE_CXX_STANDARD 20)

add_executable(DA2425_PROJ2
        main.cpp
        ReadData/read.h
        ReadData/read.cpp
)