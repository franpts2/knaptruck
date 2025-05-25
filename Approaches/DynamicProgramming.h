/**
 * @file DynamicProgramming.h
 * @brief Header for dynamic programming solution to the pallet loading problem
 */

#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

#include <iostream>

/**
 * @brief Dynamic programming solution for the 0/1 Knapsack problem
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param capacity Maximum weight capacity of the truck
 * @param usedItems Output array that will indicate which pallets were selected
 * @return The maximum total profit achievable
 * @note When multiple solutions have the same profit, solutions with fewer
 *       pallets are preferred. If pallet counts are equal, solutions with
 *       pallets having lower indices are prioritized.
 */
unsigned int knapsackDP(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, bool usedItems[]);

#endif // DYNAMICPROGRAMMING_H