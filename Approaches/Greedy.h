/**
 * @file Greedy.h
 * @brief Header for greedy approximation algorithms for 0/1 Knapsack
 */

#ifndef GREEDY_H
#define GREEDY_H
#include <vector>
#include <string>

/**
 * @brief Structure to hold greedy approximation solution
 * @var GreedySol::total_profit Total profit of selected pallets
 * @var GreedySol::total_weight Total weight of selected pallets
 * @var GreedySol::pallet_count Number of pallets selected
 * @var GreedySol::used_pallets Boolean vector indicating which pallets are used
 * @var GreedySol::approach_name Name of the greedy approach used
 */
struct GreedySol
{
    unsigned int total_profit;
    unsigned int total_weight;
    unsigned int pallet_count;
    std::vector<bool> used_pallets;
    std::string approach_name;
};

/**
 * @brief Greedy approximation using weight-to-profit ratio
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @return GreedySol containing the solution
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
 * @note When comparing solutions, the function prioritizes higher total profit.
 *       If profits are equal, it selects the solution with fewer pallets.
 *       If pallet counts are also equal, it chooses the solution with lower total weight.
 */
GreedySol knapsackGreedyMaximum(unsigned int profits[], unsigned int weights[],
                                unsigned int n, unsigned int max_weight);

#endif // GREEDY_H