#include "DynamicProgramming.h"

unsigned int knapsackDP(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, bool usedItems[]) {
    unsigned int table[n + 1][capacity + 1];

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

    for (unsigned int i = 1; i <= n; i++)
      usedItems[i] = false;



    return 0;
}