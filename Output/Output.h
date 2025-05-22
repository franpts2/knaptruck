/**
 * @file Output.h
 * @brief Output handling for exhaustive search results
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "../Approaches/Exhaustive.h"
#include "../Approaches/Backtracking.h"
#include "../Approaches/Greedy.h"
#include <vector>

struct BFSol;
struct BTSol;
struct GreedySol;

/**
 * @brief Displays the exhaustive search solution
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param solution The solution to display
 * @param executionTime Execution time in milliseconds
 */
void OutputExhaustiveSolution(unsigned int pallets[], unsigned int weights[],
                              unsigned int profits[], unsigned int n,
                              const BFSol &solution, double executionTime);

/**
 * @brief Displays the dynamic programming solution
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param totalProfit Total profit of the solution
 * @param totalWeight Total weight of the solution
 * @param palletCount Number of pallets used
 * @param usedItems Boolean array indicating which items are used
 * @param executionTime Execution time in milliseconds
 */
void OutputDynamicProgramming(unsigned int pallets[], unsigned int weights[],
                              unsigned int profits[], unsigned int n,
                              unsigned int totalProfit, unsigned int totalWeight,
                              unsigned int palletCount, const bool usedItems[],
                              double executionTime);

/**
 * @brief Displays the backtracking solution
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param solution The solution to display
 * @param executionTime Execution time in milliseconds
 */
void OutputBacktracking(unsigned int pallets[], unsigned int weights[],
                        unsigned int profits[], unsigned int n,
                        const BTSol &solution, double executionTime);

/**
 * @brief Displays the greedy approximation solution
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param solution The greedy solution to display
 * @param executionTime Execution time in milliseconds
 */
void OutputGreedyApproximation(unsigned int pallets[], unsigned int weights[],
                               unsigned int profits[], unsigned int n,
                               const GreedySol &solution, double executionTime);

/**
 * @brief Displays the integer linear programming solution
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck capacity
 * @param totalProfit Total profit of the solution
 * @param totalWeight Total weight of the solution
 * @param selectedIndices Vector of indices of selected pallets
 * @param executionTime Execution time in milliseconds
 */
void OutputLinearProgramming(unsigned int pallets[], unsigned int weights[],
                            unsigned int profits[], unsigned int n,
                            unsigned int capacity, int totalProfit, int totalWeight,
                            const std::vector<int>& selectedIndices, double executionTime);

#endif // OUTPUT_H