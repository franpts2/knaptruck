/**
 * @file Exhaustive.h
 * @brief Header for brute-force approach for 0/1 Knapsack
 */

#ifndef EXHAUSTIVE_H
#define EXHAUSTIVE_H
#include <vector>

/**
 * @brief Structure to hold pallet loading solution for brute-force approach
 * @var BFSol::total_profit Total profit of selected pallets
 * @var BFSol::total_weight Total weight of selected pallets
 * @var BFSol::pallet_count Number of pallets selected
 * @var BFSol::used_pallets Boolean vector indicating which pallets are used
 */
struct BFSol
{
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
 * @note When multiple solutions have the same profit, solutions with fewer
 *       pallets are preferred. If pallet counts are equal, solutions with
 *       pallets having lower indices are prioritized.
 * @note Time Complexity: O(2^n) where n is the number of pallets
 * @note Space Complexity: O(n) for storing the solution
 */
BFSol knapsackBF(unsigned int profits[], unsigned int weights[],
                 unsigned int n, unsigned int max_weight);

#endif // EXHAUSTIVE_H