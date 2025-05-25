/**
 * @file Output.h
 * @brief Header file for output formatting and display of algorithm results
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <string>
#include "../Approaches/Exhaustive.h"
#include "../Approaches/Greedy.h"
#include "../Approaches/Backtracking.h"

/**
 * @brief Displays the results of the exhaustive search algorithm
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param solution The solution structure returned by the exhaustive algorithm
 * @param executionTime Time taken to execute the algorithm in milliseconds
 */
void OutputExhaustiveSolution(unsigned int pallets[], unsigned int weights[],
                              unsigned int profits[], unsigned int n,
                              const BFSol &solution, double executionTime);

/**
 * @brief Displays the results of the dynamic programming algorithm
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param totalProfit Total profit achieved by the solution
 * @param totalWeight Total weight of the selected pallets
 * @param palletCount Number of pallets selected in the solution
 * @param usedItems Boolean array indicating which pallets were selected
 * @param executionTime Time taken to execute the algorithm in milliseconds
 */
void OutputDynamicProgramming(unsigned int pallets[], unsigned int weights[],
                              unsigned int profits[], unsigned int n,
                              unsigned int totalProfit, unsigned int totalWeight,
                              unsigned int palletCount, const bool usedItems[],
                              double executionTime);

/**
 * @brief Displays the results of the backtracking algorithm
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param solution The solution structure returned by the backtracking algorithm
 * @param executionTime Time taken to execute the algorithm in milliseconds
 */
void OutputBacktracking(unsigned int pallets[], unsigned int weights[],
                        unsigned int profits[], unsigned int n,
                        const BTSol &solution, double executionTime);

/**
 * @brief Displays the results of the greedy approximation algorithms
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param solution The solution structure returned by the greedy algorithm
 * @param executionTime Time taken to execute the algorithm in milliseconds
 */
void OutputGreedyApproximation(unsigned int pallets[], unsigned int weights[],
                               unsigned int profits[], unsigned int n,
                               const GreedySol &solution, double executionTime);

/**
 * @brief Displays the results of the integer linear programming algorithm
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Maximum truck capacity
 * @param totalProfit Total profit achieved by the solution
 * @param totalWeight Total weight of the selected pallets
 * @param selectedIndices Vector of indices of the selected pallets
 * @param executionTime Time taken to execute the algorithm in milliseconds
 */
void OutputIntegerLinearProgramming(unsigned int pallets[], unsigned int weights[],
                                    unsigned int profits[], unsigned int n,
                                    unsigned int capacity, int totalProfit, int totalWeight,
                                    const std::vector<int> &selectedIndices, double executionTime);

/**
 * @brief Displays comparative results for all implemented algorithms
 * @param names Vector of algorithm names
 * @param times Vector of execution times for each algorithm
 * @param spaceComplexities Vector of space complexity descriptions
 * @param accuracyAlgorithms Vector of accuracy/optimality descriptions
 * @param profits Vector of total profits achieved by each algorithm
 *
 * @note Displays a comparative table with performance metrics for all algorithms,
 * including execution time, space complexity, accuracy, and solution quality.
 */
void OutputCompareAllAlgorithms(const std::vector<std::string> &names,
                                const std::vector<double> &times,
                                const std::vector<std::string> &spaceComplexities,
                                const std::vector<std::string> &accuracyAlgorithms,
                                const std::vector<unsigned int> &profits);

#endif // OUTPUT_H
