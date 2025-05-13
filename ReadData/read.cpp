#include "read.h"


unsigned int readPallets(const std::string &filename, std::vector<unsigned int> &pallets, std::vector<unsigned int> &weights, std::vector<unsigned int> &profits) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 0;
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

        pallets.push_back(std::stoi(pallet));
        weights.push_back(std::stoi(weight));
        profits.push_back(std::stoi(profit));

        ++index;
    }

    file.close();
    return index;
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
