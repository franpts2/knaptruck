/**
* @file Exhaustive.h
 * @brief Header for brute-force pallet loading implementation
 */

#ifndef EXHAUSTIVE_H
#define EXHAUSTIVE_H
#include <vector>

/**
 * @brief Structure to hold pallet loading solution
 */
struct BFSol {
    unsigned int total_profit;
    unsigned int total_weight;
    unsigned int pallet_count;
    std::vector<bool> used_pallets;
};

/**
 * @brief Brute-force pallet loading algorithm
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @return BFSol containing optimal loading
 */
BFSol knapsackBF(unsigned int profits[], unsigned int weights[],
                                      unsigned int n, unsigned int max_weight);

#endif // EXHAUSTIVE_H