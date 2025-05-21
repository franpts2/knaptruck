add_compile_definitions()
cmake_minimum_required(VERSION 3.30)
project(DA2425_PROJ2)

set(CMAKE_CXX_STANDARD 20)

add_executable(DA2425_PROJ2
        main.cpp
        ReadData/read.cpp
        Menu/Menu.cpp
        Menu/MenuTesting.cpp
        Approaches/DynamicProgramming.cpp
        Approaches/Exhaustive.cpp
        Approaches/Backtracking.cpp
        Approaches/Greedy.cpp
        InputOutput/Input.cpp
        InputOutput/Output.cpp
        InputOutput/ProgressBar.cpp
)