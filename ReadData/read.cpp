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

      	try {
        std::stringstream ss(line);
        std::string pallet, weight, profit;

        std::getline(ss, pallet, ',');
        std::getline(ss, weight, ',');
        std::getline(ss, profit, ',');

        pallets[index] = std::stoi(pallet);
        weights[index] = std::stoi(weight);
        profits[index] = std::stoi(profit);

        ++index;
        }
        catch (const std::invalid_argument &e) {
            std::cerr << "Invalid data in line: " << line << std::endl;
            continue; // Skip this line and continue with the next one
        }
        catch (const std::out_of_range &e) {
            std::cerr << "Data out of range in line: " << line << std::endl;
            continue; // Skip this line and continue with the next one
        }
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
