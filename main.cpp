#include <iostream>

#include "Menu/Menu.h"
#include "Menu/MenuTesting.h"
#include "ReadData/read.h"
#include "Approaches/DynamicProgramming.h"

int main() {
    std::cout << "Choose mode:" << std::endl;
    std::cout << "1. Normal Mode (Regular Menu)" << std::endl;
    std::cout << "2. Testing Mode (Dataset Testing Menu)" << std::endl;
    std::cout << "Option: ";
    
    int modeChoice;
    std::cin >> modeChoice;
    
    if (modeChoice == 2) {
        // Run the testing menu for datasets 1-10
        runTestingMenu();
        return 0;
    }
    
    // Original code for normal mode
    unsigned int trucksAndPallets[2];
    readTrucks("datasets/TruckAndPallets_01.csv", trucksAndPallets);

    const unsigned int n = trucksAndPallets[1];
    unsigned int pallets[n];
    unsigned int weights[n];
    unsigned int profits[n];

    readPallets("datasets/Pallets_01.csv", pallets, weights, profits);

    // Get user menu selection and handle it
    int option = optionsMenu();
    // Maximum number of pallets that can be loaded
    unsigned int max_pallets = n; 
    handleMenuOption(option, pallets, weights, profits, n, trucksAndPallets[0], max_pallets);

    return 0;
}
