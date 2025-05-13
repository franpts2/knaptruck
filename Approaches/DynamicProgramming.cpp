#include "DynamicProgramming.h"

unsigned int knapsackDP(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, bool usedItems[]) {
    unsigned int table[n + 1][capacity + 1];

    // Initialize table: first row and first column to 0
    for (unsigned int i = 0; i <= n; i++)
        table[i][0] = 0;
    for (unsigned int w = 0; w <= capacity; w++)
        table[0][w] = 0;

    // Fill table
    for (unsigned int i = 1; i <= n; i++) {
        for (unsigned int w = 1; w <= capacity; w++) {
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

    // Optional: print table for debugging

    for (unsigned int i = 0; i <= n; i++) {
        for (unsigned int w = 0; w <= capacity; w++) {
            std::cout << table[i][w] << " ";
        }
        std::cout << std::endl;
    }


    return table[n][capacity];
}
