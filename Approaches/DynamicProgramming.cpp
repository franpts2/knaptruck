#include "DynamicProgramming.h"
#include "../InputOutput/ProgressBar.h"

unsigned int knapsackDP(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, bool usedItems[]) {
    unsigned int table[n + 1][capacity + 1];

    // Initialize progress bar - total operations is roughly n*capacity
    unsigned long long total_operations = (unsigned long long)(n) * capacity;
    ProgressBar progress(total_operations);
    unsigned long long current_operation = 0;

    // Initialize table: first row and first column to 0
    for (unsigned int i = 0; i <= n; i++)
        table[i][0] = 0;
    for (unsigned int w = 0; w <= capacity; w++)
        table[0][w] = 0;

    // Fill table
    for (unsigned int i = 1; i <= n; i++) {
        for (unsigned int w = 1; w <= capacity; w++) {
            // Update progress counter
            current_operation++;
            
            // Update progress bar every 10000 operations to reduce overhead
            if (current_operation % 10000 == 0) {
                if (progress.shouldShow()) {
                    progress.update(current_operation);
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

    // Complete progress bar if it was displayed
    progress.complete();

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

    // Removed debug printing of the table as it can be overwhelming for large datasets
    // Only keeping the actual result

    return table[n][capacity];
}