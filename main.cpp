/**
 * @file main.cpp
 * @brief Entry point for the Truck Packing Optimization application
 * 
 * This file contains the main function that initializes and launches
 * the Truck Packing Optimization application, which solves the knapsack
 * problem for logistics optimization using various algorithms.
 */

#include <iostream>
#include "Menu/Menu.h"
#include "ReadData/read.h"
#include "Approaches/DynamicProgramming.h"

int main()
{
    std::cout << std::endl
              << "Hello user!" << std::endl;
    std::cout << "Welcome to the Truck Packing Optimization Tool!" << std::endl
              << std::endl;
    std::cout << "This tool helps solve the knapsack problem for logistics optimization." << std::endl;
    mainMenu();
    return 0;
}


