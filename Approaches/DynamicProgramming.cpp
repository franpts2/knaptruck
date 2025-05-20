#include "DynamicProgramming.h"
#include "../InputOutput/ProgressBar.h"
#include <vector>
#include <iostream>

unsigned int knapsackDP(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, bool usedItems[]) {
    // Use dynamic memory allocation (heap) instead of stack allocation
    std::vector<std::vector<unsigned int>> table(n + 1, std::vector<unsigned int>(capacity + 1, 0));

    // Initialize progress bar - total operations is roughly n*capacity
    unsigned long long total_operations = (unsigned long long)(n) * capacity;
    ProgressBar progress(total_operations);
    unsigned long long current_operation = 0;
    bool user_cancelled = false;

    // Fill table
    for (unsigned int i = 1; i <= n && !user_cancelled; i++) {
        for (unsigned int w = 1; w <= capacity && !user_cancelled; w++) {
            // Update progress counter
            current_operation++;
            
            // Update progress bar every 10000 operations to reduce overhead
            if (current_operation % 10000 == 0) {
                if (progress.shouldShow()) {
                    // Update returns false if user pressed escape
                    if (!progress.update(current_operation)) {
                        user_cancelled = true;
                        break;
                    }
                }
            }
            
            if (weights[i-1] > w) {
                table[i][w] = table[i-1][w];
            } else {
                unsigned int value = table[i-1][w - weights[i-1]] + profits[i-1];
                if (value > table[i-1][w]) {
                    table[i][w] = value;
                } else {
                    table[i][w] = table[i-1][w];
                }
            }
        }
    }

    // Complete progress bar if it was shown and user didn't cancel
    if (!user_cancelled) {
        progress.complete();
    }
    
    // If user cancelled, inform them and return 0
    if (user_cancelled) {
        std::cout << "\nOperation cancelled by user. Returning to menu." << std::endl;
        
        // Clear used items array to indicate cancellation
        for (unsigned int i = 0; i < n; i++) {
            usedItems[i] = false;
        }
        
        return 0;
    }

    // Backtracking to determine which items were used
    for (unsigned int i = 0; i < n; i++) {
        usedItems[i] = false;
    }
    unsigned int w = capacity;
    for (int i = n; i > 0; i--) {
        if (table[i][w] != table[i-1][w]) {
            usedItems[i-1] = true;
            w -= weights[i-1];
        }
    }

    // Return the maximum profit
    return table[n][capacity];
}