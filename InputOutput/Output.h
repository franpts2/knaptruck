/**
* @file Output.h
 * @brief Output handling for exhaustive search results
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "Exhaustive.h"
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

#endif // OUTPUT_H