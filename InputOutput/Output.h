/**
* @file Output.h
 * @brief Output handling for exhaustive search results
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "../Approaches/Exhaustive.h"
#include <vector>

struct BFSol;

/**
 * @brief Displays the exhaustive search solution
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param solution The solution to display
 */
void OutputExhaustiveSolution(unsigned int pallets[], unsigned int weights[],
                             unsigned int profits[], unsigned int n,
                             const BFSol &solution);

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
                             long long executionTime);

#endif // OUTPUT_H