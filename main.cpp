#include <iostream>
#include "ReadData/read.h"

int main() {

    std::vector<unsigned int> pallets;
    std::vector<unsigned int> weights;
    std::vector<unsigned int> profits;

    unsigned int trucksAndPallets[2];

    unsigned int n = readPallets("datasets/Pallets_01.csv", pallets, weights, profits);
    readTrucks("datasets/TruckAndPallets_01.csv", trucksAndPallets);


    // to see if it's working
    for (unsigned int i = 0; i < n; i++) {
        std::cout << "Pallet: " << pallets[i] << ", Weight: " << weights[i] << ", Profit: " << profits[i] << std::endl;
    }
    std::cout << "Capacity: " << trucksAndPallets[0] << ", Pallets: " << trucksAndPallets[1] << std::endl;


    return 0;
}
