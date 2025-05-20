/**
 * @file Backtracking.cpp
 * @brief Backtracking pallet loading implementation
 */

#include "Backtracking.h"
#include <vector>
#include <algorithm>
#include <climits>

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
                  BTSol &bestSolution) {
    
    // Base case: we've processed all items
    if (curIndex == n) {
        // Check if current solution is better than the best found so far
        if (curProfit > bestSolution.total_profit || 
           (curProfit == bestSolution.total_profit && curCount < bestSolution.pallet_count) ||
           (curProfit == bestSolution.total_profit && curCount == bestSolution.pallet_count && 
            curWeight < bestSolution.total_weight)) {
            
            bestSolution.total_profit = curProfit;
            bestSolution.total_weight = curWeight;
            bestSolution.pallet_count = curCount;
            bestSolution.used_pallets = curItems;
        }
        return;
    }
    
    // Try including the current pallet
    if (curWeight + weights[curIndex] <= max_weight && curCount + 1 <= max_pallets) {
        curItems[curIndex] = true;
        knapsackBTRec(
            profits, weights, n, 
            curIndex + 1, 
            max_weight, max_pallets,
            curWeight + weights[curIndex], 
            curProfit + profits[curIndex],
            curCount + 1,
            curItems, 
            bestSolution
        );
        curItems[curIndex] = false; // Backtrack
    }
    
    // Try excluding the current pallet
    knapsackBTRec(
        profits, weights, n, 
        curIndex + 1, 
        max_weight, max_pallets,
        curWeight, 
        curProfit,
        curCount,
        curItems, 
        bestSolution
    );
}

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
                unsigned int max_pallets) {
    
    // Initialize the best solution
    BTSol bestSolution = {0, 0, 0, std::vector<bool>(n, false)};
    
    // Initialize the current items array
    std::vector<bool> curItems(n, false);
    
    // Call the recursive function to start backtracking
    knapsackBTRec(
        profits, weights, n,
        0,
        max_weight, max_pallets,
        0, 0, 0,
        curItems,
        bestSolution
    );
    
    return bestSolution;
}