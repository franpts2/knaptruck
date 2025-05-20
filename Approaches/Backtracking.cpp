/**
 * @file Backtracking.cpp
 * @brief Backtracking pallet loading implementation
 */

#include "Backtracking.h"
#include "../InputOutput/ProgressBar.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <limits>
#include <iostream>

// Global variables to track progress (used only in the backtracking algorithm)
static unsigned long long g_nodes_visited = 0;
static unsigned long long g_total_nodes = 0;
static ProgressBar* g_progress = nullptr;
static bool g_user_cancelled = false;

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
    
    // If user cancelled, stop recursion
    if (g_user_cancelled) {
        return;
    }
    
    // Increment the number of nodes visited for progress tracking
    g_nodes_visited++;
    
    // Check for cancellation
    if (g_nodes_visited % 10000 == 0 && g_progress != nullptr) {
        // Update returns false if user pressed escape
        if (!g_progress->update(g_nodes_visited)) {
            g_user_cancelled = true;
            return;
        }
    }
    
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
    
    // Reset and initialize global progress tracking variables
    g_nodes_visited = 0;
    g_user_cancelled = false;
    
    // Only for extremely large datasets (like dataset 6 with 4000+ pallets)
    if (n > 1000) {
        // Create a hidden progress bar for cancellation detection
        ProgressBar hiddenProgress(1, true);
        g_progress = &hiddenProgress;
        
        // Show the coffee message
        hiddenProgress.showLargeDatasetMessage();
        
        // Call the recursive function to start backtracking
        knapsackBTRec(
            profits, weights, n,
            0,
            max_weight, max_pallets,
            0, 0, 0,
            curItems,
            bestSolution
        );
        
        if (!g_user_cancelled) {
            std::cout << "\nFinished! Hope you enjoyed your coffee! ☕" << std::endl;
        }
    } else {
        // For normal datasets, use the standard estimation
        g_total_nodes = static_cast<unsigned long long>(std::pow(2, n)) * 2;
        
        // Create a progress bar
        ProgressBar progress(g_total_nodes);
        g_progress = &progress;
        
        // Call the recursive function to start backtracking
        knapsackBTRec(
            profits, weights, n,
            0,
            max_weight, max_pallets,
            0, 0, 0,
            curItems,
            bestSolution
        );
        
        // Finalize progress bar if it was shown
        if (!g_user_cancelled) {
            g_progress->complete();
        }
    }
    
    // If user cancelled, return an empty solution
    if (g_user_cancelled) {
        std::cout << "\nOperation cancelled by user. Returning to menu." << std::endl;
        
        // Clear the best solution to indicate cancellation
        bestSolution = {0, 0, 0, std::vector<bool>(n, false)};
    }
    
    // Reset global pointer
    g_progress = nullptr;
    
    return bestSolution;
}