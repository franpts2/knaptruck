#include <iostream>
#include "ReadData/read.h"
#include "Approaches/DynamicProgramming.h"

int main() {

    unsigned int trucksAndPallets[2];
    readTrucks("datasets-extra/TruckAndPallets_05.csv", trucksAndPallets);

    unsigned int n = trucksAndPallets[1];

    unsigned int pallets[n];
    unsigned int weights[n];
    unsigned int profits[n];

    readPallets("datasets-extra/Pallets_05.csv", pallets, weights, profits);

    bool usedItems[n] = {false};
    unsigned int finalWeight = knapsackDP(profits, weights, n, trucksAndPallets[0], usedItems);


    // to see if it's working
    for (unsigned int i = 0; i < n; i++) {
        std::cout << "Pallet: " << pallets[i] << ", Weight: " << weights[i] << ", Profit: " << profits[i] << std::endl;
    }
    std::cout << "Capacity: " << trucksAndPallets[0] << ", Pallets: " << trucksAndPallets[1] << std::endl;


    return 0;
}
