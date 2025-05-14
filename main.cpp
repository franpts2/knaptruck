#include <iostream>

#include "Menu/Menu.h"
#include "ReadData/read.h"

int main() {

    std::vector<unsigned int> pallets;
    std::vector<unsigned int> weights;
    std::vector<unsigned int> profits;

    unsigned int trucksAndPallets[2];

    unsigned int n = readPallets("datasets/Pallets_01.csv", pallets, weights, profits);
    readTrucks("datasets/TruckAndPallets_01.csv", trucksAndPallets);

    // // to see if it's working
    // for (unsigned int i = 0; i < n; i++) {
    //     std::cout << "Pallet: " << pallets[i] << ", Weight: " << weights[i] << ", Profit: " << profits[i] << std::endl;
    // }
    // std::cout << "Capacity: " << trucksAndPallets[0] << ", Pallets: " << trucksAndPallets[1] << std::endl;

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
