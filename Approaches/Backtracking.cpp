#include "Backtracking.h"
#include "../Output/ProgressBar.h"
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

void knapsackBTRec(unsigned int profits[], unsigned int weights[],
                  unsigned int n, unsigned int curIndex,
                  unsigned int max_weight, unsigned int curWeight, 
                  unsigned int curProfit, unsigned int curCount, 
                  std::vector<bool> &curItems, BTSol &bestSolution) {
    
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
    if (curWeight + weights[curIndex] <= max_weight) {
        curItems[curIndex] = true;
        knapsackBTRec(
            profits, weights, n, 
            curIndex + 1, 
            max_weight,
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
        max_weight,
        curWeight, 
        curProfit,
        curCount,
        curItems, 
        bestSolution
    );
}

BTSol knapsackBT(unsigned int profits[], unsigned int weights[],
                unsigned int n, unsigned int max_weight) {
    
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
            max_weight,
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
            max_weight,
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