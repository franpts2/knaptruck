#include "DynamicProgramming.h"

unsigned int knapsackDP(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, bool usedItems[]) {
    unsigned int table[n + 1][capacity + 1];

    // first row
    for (unsigned int i = 0; i <= capacity; i++)
        table[0][i] = (i >= weights[0]) ? profits[0] : 0;

    // capacity 0
    for (unsigned int i = 1; i <= n; i++)
        table[i][0] = 0;

    for (unsigned int i = 1; i <= n; i++) {
        for (unsigned int w = 1; w <= capacity; w++) {
            if(w < weights[i]) {
                table[i][w] = table[i - 1][w]; // item does not fit
            }
            else {
                unsigned int profitUsingItemI = table[i - 1][w - weights[i]] + profits[i];
                if(profitUsingItemI > table[i - 1][w]) {
                    table[i][w] = profitUsingItemI;
                }
                else {
                    table[i][w] = table[i - 1][w];
                }
            }
        }
    }

    //backtracking to determine which items were used
    for(unsigned int i = 0; i < n; i++) {
        usedItems[i] = false;
    }
    unsigned int remainingWeight = capacity;
    unsigned int curItem = n - 1;
    for(unsigned int i = n - 1; i > 0; i--) {
        // Stop earlier of the all the items have already been added to the solution
        if(remainingWeight == 0) break;

        // An item is used if not including reduces the total value for a knapsack of the same size
        if(table[i][remainingWeight] != table[i-1][remainingWeight]) {
            usedItems[i] = true;
            remainingWeight -= weights[i];
            curItem--;
        }
    }
    // If remainingWeight > 0, then the first item is used
    if(remainingWeight > 0) {
        usedItems[0] = true;
    }

    return table[n-1][capacity];
}