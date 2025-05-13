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
    for (unsigned int i = 1; i <= n; i++)
      usedItems[i] = false;

    unsigned int w = capacity;
    for (unsigned int i = n; i > 0 && w > 0; i--) {
        if (table[i][w] != table[i - 1][w]) {
            usedItems[i - 1] = true; // Item i-1 is used
            w -= weights[i - 1];
        } else {
            usedItems[i - 1] = false;
        }
    }

    return table[n][capacity];
}