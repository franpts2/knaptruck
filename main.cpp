#include <iostream>

#include "Menu/Menu.h"
#include "Menu/MenuTesting.h"
#include "ReadData/read.h"
#include "Approaches/DynamicProgramming.h"

int main()
{
    std::cout << std::endl
              << "Hello user!" << std::endl;
    std::cout << "Welcome to the Truck Packing Optimization Tool!" << std::endl
              << std::endl;
    std::cout << "This tool helps solve the knapsack problem for logistics optimization." << std::endl;
    // Unified menu: always use mainMenu from Menu.cpp
    mainMenu();
    return 0;
}
