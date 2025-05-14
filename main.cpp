#include <iostream>
#include "ReadData/read.h"
#include "Approaches/DynamicProgramming.h"

int main() {

    unsigned int trucksAndPallets[2];
    readTrucks("datasets/truckTest_05.csv", trucksAndPallets);

    const unsigned int n = trucksAndPallets[1];

    unsigned int pallets[n];
    unsigned int weights[n];
    unsigned int profits[n];

    readPallets("datasets/test_05.csv", pallets, weights, profits);


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
    /*std::cout << "\nCapacity: " << trucksAndPallets[0] << ", Pallets: " << trucksAndPallets[1] << std::endl;
    for (unsigned int i = 0; i < n; i++) {
        std::cout << "Pallet: " << pallets[i] << ", Weight: " << weights[i] << ", Profit: " << profits[i] << std::endl;
    }*/


    return 0;
}
