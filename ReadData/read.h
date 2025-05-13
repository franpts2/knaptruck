#ifndef READ_H
#define READ_H

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <sstream>

unsigned int readPallets(const std::string &filename, std::vector<unsigned int> &pallets, std::vector<unsigned int> &weights, std::vector<unsigned int> &profits);

void readTrucks(const std::string &filename, unsigned int *trucksAndPallets);

#endif //READ_H
