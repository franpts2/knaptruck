#ifndef READ_H
#define READ_H

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <sstream>

void readPallets(const std::string &filename,unsigned int pallets[], unsigned int weights[], unsigned int profits[]);

void readTrucks(const std::string &filename, unsigned int *trucksAndPallets);

#endif //READ_H
