/**
 * @file Backtracking.h
 * @brief Header for backtracking pallet loading implementation
 */

#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include <vector>

/**
 * @brief Structure to hold pallet loading solution
 */
struct BTSol {
    unsigned int total_profit;
    unsigned int total_weight;
    unsigned int pallet_count;
    std::vector<bool> used_pallets;
};

/**
 * @brief Helper function for backtracking algorithm
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param curIndex Current index of pallet being considered
 * @param max_weight Maximum weight capacity of truck
 * @param max_pallets Maximum number of pallets allowed
 * @param curWeight Current accumulated weight
 * @param curProfit Current accumulated profit
 * @param curCount Current count of pallets
 * @param curItems Current selection of pallets
 * @param bestSolution Reference to the best solution found
 */
void knapsackBTRec(unsigned int profits[], unsigned int weights[],
                  unsigned int n, unsigned int curIndex,
                  unsigned int max_weight, unsigned int max_pallets,
                  unsigned int curWeight, unsigned int curProfit, 
                  unsigned int curCount, std::vector<bool> &curItems, 
                  BTSol &bestSolution);

/**
 * @brief Backtracking pallet loading algorithm
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @param max_pallets Maximum number of pallets allowed
 * @return BTSol containing optimal loading
 */
BTSol knapsackBT(unsigned int profits[], unsigned int weights[],
                unsigned int n, unsigned int max_weight,
                unsigned int max_pallets);

#endif // BACKTRACKING_H