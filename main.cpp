#include <iostream>
#include "ReadData/read.h"
#include "Approaches/DynamicProgramming.h"

int main() {

    std::vector<unsigned int> pallets;
    std::vector<unsigned int> weights;
    std::vector<unsigned int> profits;

    unsigned int trucksAndPallets[2];

    unsigned int n = readPallets("datasets-extra/Pallets_05.csv", pallets, weights, profits);
    readTrucks("datasets-extra/TruckAndPallets_05.csv", trucksAndPallets);

    bool usedItems[n] = {false};

    unsigned int finalWeight = knapsackDP(profits, weights, n, trucksAndPallets[0], usedItems);


    // to see if it's working
    for (unsigned int i = 0; i < n; i++) {
        std::cout << "Pallet: " << pallets[i] << ", Weight: " << weights[i] << ", Profit: " << profits[i] << std::endl;
    }
    std::cout << "Capacity: " << trucksAndPallets[0] << ", Pallets: " << trucksAndPallets[1] << std::endl;


    return 0;
}
