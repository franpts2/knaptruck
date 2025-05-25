/**
 * @file Backtracking.h
 * @brief Header for backtracking algorithm for 0/1 Knapsack
 */

#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include <vector>

/**
 * @brief Structure to hold pallet loading solution for backtracking approach
 * @var BTSol::total_profit Total profit of selected pallets
 * @var BTSol::total_weight Total weight of selected pallets
 * @var BTSol::pallet_count Number of pallets selected
 * @var BTSol::used_pallets Boolean vector indicating which pallets are used
 */
struct BTSol
{
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
 * @param curWeight Current accumulated weight
 * @param curProfit Current accumulated profit
 * @param curCount Current count of pallets
 * @param curItems Current selection of pallets
 * @param bestSolution Reference to the best solution found
 * @note Time Complexity: O(2^n) worst case, but typically better than exhaustive search due to pruning
 * @note Space Complexity: O(n) for recursion stack and storing the solution
 */
void knapsackBTRec(unsigned int profits[], unsigned int weights[],
                   unsigned int n, unsigned int curIndex,
                   unsigned int max_weight, unsigned int curWeight,
                   unsigned int curProfit, unsigned int curCount,
                   std::vector<bool> &curItems, BTSol &bestSolution);

/**
 * @brief Backtracking pallet loading algorithm
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @return BTSol containing optimal loading
 * @note Time Complexity: O(2^n) worst case, but typically better than exhaustive search due to pruning
 * @note Space Complexity: O(n) for recursion stack and storing the solution
 */
BTSol knapsackBT(unsigned int profits[], unsigned int weights[],
                 unsigned int n, unsigned int max_weight);

#endif // BACKTRACKING_H