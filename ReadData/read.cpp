#include "read.h"

#include <iostream>
#include <fstream>
#include <climits>
#include <sstream>


void readPallets(const std::string &filename) {
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
        std::string pallet, weight, profit;

        std::getline(ss, pallet, ',');
        std::getline(ss, weight, ',');
        std::getline(ss, profit, ',');
    }

    file.close();
}

void readTrucks(const std::string &filename) {
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
    }

    file.close();
}
