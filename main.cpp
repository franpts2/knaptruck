#include <iostream>

#include "Menu/Menu.h"
#include "Menu/MenuTesting.h"
#include "ReadData/read.h"
#include "Approaches/DynamicProgramming.h"

int main() {
    std::cout << std::endl << "Hello user!" << std::endl;
    std::cout << "Welcome to the Truck Packing Optimization Tool!" << std::endl << std::endl;
    std::cout << "This tool helps solve the knapsack problem for logistics optimization." << std::endl;
    

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
    
    std::cout << "\nWelcome to Truck Packing Optimization Tool!" << std::endl;
    std::cout << "Would you like to enter pallet data interactively?" << std::endl;
    std::cout << "1. Yes, enter data manually" << std::endl;
    std::cout << "2. No, use default dataset" << std::endl;
    std::cout << "Option: ";
    
    int dataChoice;
    std::cin >> dataChoice;
    
    if (dataChoice == 1) {
        // Run interactive data entry
        unsigned int* data = interactiveDataEntry();
        
        // Extract data from the result array
        unsigned int capacity = data[0];
        unsigned int n = data[1];
        unsigned int max_pallets = data[2];
        
        // Extract arrays
        unsigned int* pallets = &data[3];
        unsigned int* weights = &data[3 + n];
        unsigned int* profits = &data[3 + 2 * n];
        
        // Show menu and handle options with user data
        int option = optionsMenu();
        handleMenuOption(option, pallets, weights, profits, n, capacity, max_pallets);
        
        // Clean up allocated memory before exiting
        delete[] data;
    }
    else {
        // Original code for normal mode with default dataset
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
    }

    return 0;
}
