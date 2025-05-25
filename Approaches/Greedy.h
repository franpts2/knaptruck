/**
 * @file Greedy.h
 * @brief Header for greedy approximation algorithms for pallet loading
 */

#ifndef GREEDY_H
#define GREEDY_H
#include <vector>
#include <string>

/**
 * @brief Structure to hold greedy approximation solution
 */
struct GreedySol
{
    unsigned int total_profit;
    unsigned int total_weight;
    unsigned int pallet_count;
    std::vector<bool> used_pallets;
    std::string approach_name; // To track which greedy approach was used
};

/**
 * @brief Greedy approximation using weight-to-profit ratio
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @return GreedySol containing the solution
 * @note Tiebreaker: If profit-to-weight ratios are equal, pallets with lower indices are prioritized
 */
GreedySol knapsackGreedyRatio(unsigned int profits[], unsigned int weights[],
                              unsigned int n, unsigned int max_weight);

/**
 * @brief Greedy approximation using profit values
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @return GreedySol containing the solution
 * @note Tiebreaker: If profits are equal, pallets with lower indices are prioritized
 */
GreedySol knapsackGreedyProfit(unsigned int profits[], unsigned int weights[],
                               unsigned int n, unsigned int max_weight);

/**
 * @brief Runs both greedy approximations and returns the better solution
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @return GreedySol containing the better solution
 */
GreedySol knapsackGreedyMaximum(unsigned int profits[], unsigned int weights[],
                                unsigned int n, unsigned int max_weight);

#endif // GREEDY_H