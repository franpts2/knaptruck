#include "read.h"


void readPallets(const std::string &filename,unsigned int pallets[], unsigned int weights[], unsigned int profits[]) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    // skip the header line
    std::getline(file, line);

    unsigned int index = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string pallet, weight, profit;

        std::getline(ss, pallet, ',');
        std::getline(ss, weight, ',');
        std::getline(ss, profit, ',');

        pallets[index] = std::stoi(pallet);
        weights[index] = std::stoi(weight);
        profits[index] = std::stoi(pallet);

        ++index;
    }

    file.close();
    return;
}

void readTrucks(const std::string &filename, unsigned int *trucksAndPallets) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    // skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string capacity, pallets;

        std::getline(ss, capacity, ',');
        std::getline(ss, pallets, ',');

        trucksAndPallets[0] = std::stoi(capacity);
        trucksAndPallets[1] = std::stoi(pallets);
    }

    file.close();
    return;
}
