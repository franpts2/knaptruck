#include <iostream>

#include "Menu/Menu.h"
#include "ReadData/read.h"
#include "Approaches/DynamicProgramming.h"

int main() {

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


    switch (optionsMenu()) {
        case 1:
            std::cout << "Running Exhaustive Search Algorithm..." << std::endl << std::endl;
            //optionExhaustiveSearch(pallets, capacity);
            break;
        case 2:
            std::cout << "Running Dynamic Programming Approach..." << std::endl << std::endl;
            //optionDynamicProgramming(pallets, capacity);
            break;
        case 3:
            std::cout << "Running Approximation Algorithm..." << std::endl << std::endl;
            //optionApproximation(pallets, capacity);
            break;
        case 4:
            std::cout << "Running Linear Integer Programming..." << std::endl << std::endl;
            //optionLinearProgramming(pallets, capacity);
            break;
        case 5:
            std::cout << "Comparing All Algorithms..." << std::endl << std::endl;
            //optionCompareAllAlgorithms(pallets, capacity);
            break;
        case 6:
            optionShowInfoMenu(pallets, trucksAndPallets[0]);
            break;
        case 7:
            std::cout << "Exiting..." << std::endl;
            return 0;
        default:
            std::cout << "Invalid option selected!" << std::endl;
            break;
    }

    return 0;
}
