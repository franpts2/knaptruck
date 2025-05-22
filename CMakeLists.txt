add_compile_definitions()
cmake_minimum_required(VERSION 3.30)
project(DA2425_PROJ2)

set(CMAKE_CXX_STANDARD 20)

add_executable(DA2425_PROJ2
        main.cpp
        ReadData/read.cpp
        Menu/Menu.cpp
        Approaches/DynamicProgramming.cpp
        Approaches/Exhaustive.cpp
        Approaches/Backtracking.cpp
        Approaches/Greedy.cpp
        Output/Output.cpp
        Output/ProgressBar.cpp
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Approaches/knapsack_solver.py
    ${CMAKE_CURRENT_BINARY_DIR}/knapsack_solver.py
    COPYONLY
)