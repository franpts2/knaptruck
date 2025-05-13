#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

#include <iostream>

unsigned int knapsackDP(std::vector<unsigned int> &profits, std::vector<unsigned int> &weights, unsigned int n, unsigned int capacity, bool usedItems[]);

#endif //DYNAMICPROGRAMMING_H
