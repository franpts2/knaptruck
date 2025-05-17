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
    readTrucks("datasets-extra/TruckAndPallets_05.csv", trucksAndPallets);

    const unsigned int n = trucksAndPallets[1];

    unsigned int pallets[n];
    unsigned int weights[n];
    unsigned int profits[n];

    readPallets("datasets-extra/Pallets_05.csv", pallets, weights, profits);


    // dynamic programming (i'll move this later)
    bool usedItems[n];
    unsigned int finalProfit = knapsackDP(profits, weights, n, trucksAndPallets[0], usedItems);


    // to see if it's working
    std::cout << "Final profit: " << finalProfit << std::endl;
    std::cout << "Used Items: ";
    for (unsigned int i = 0; i < n; i++) {
        if (usedItems[i]) {
            std::cout << pallets[i] << " ";
        }
    }
    std::cout << std::endl;

    // Get user menu selection and handle it with the updated function
    int option = optionsMenu();
    // Maximum number of pallets that can be loaded
    // For simplicity, we're using n here, but this could be adjusted based on requirements
    unsigned int max_pallets = n; 
    handleMenuOption(option, pallets, weights, profits, n, trucksAndPallets[0], max_pallets);

    return 0;
}
