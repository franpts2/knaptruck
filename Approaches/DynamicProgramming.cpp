#include "DynamicProgramming.h"
#include "../Output/ProgressBar.h"
#include <vector>
#include <iostream>

unsigned int knapsackDP(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, bool usedItems[])
{
    // Use dynamic memory allocation (heap) instead of stack allocation
    std::vector<std::vector<unsigned int>> table(n + 1, std::vector<unsigned int>(capacity + 1, 0));

    // Count table: stores the number of pallets used for each solution
    std::vector<std::vector<unsigned int>> countTable(n + 1, std::vector<unsigned int>(capacity + 1, 0));

    // IndexSum table: stores a score based on indices of pallets used (lower indices are preferred)
    std::vector<std::vector<unsigned int>> indexSumTable(n + 1, std::vector<unsigned int>(capacity + 1, 0));

    // Initialize progress bar - total operations is roughly n*capacity
    unsigned long long total_operations = (unsigned long long)(n)*capacity;
    ProgressBar progress(total_operations);
    unsigned long long current_operation = 0;
    bool user_cancelled = false;

    // Fill table
    for (unsigned int i = 1; i <= n && !user_cancelled; i++)
    {
        for (unsigned int w = 1; w <= capacity && !user_cancelled; w++)
        {
            // Update progress counter
            current_operation++;

            // Update progress bar every 10000 operations to reduce overhead
            if (current_operation % 10000 == 0)
            {
                if (progress.shouldShow())
                {
                    // Update returns false if user pressed escape
                    if (!progress.update(current_operation))
                    {
                        user_cancelled = true;
                        break;
                    }
                }
            }

            if (weights[i - 1] > w)
            {
                // Item doesn't fit, copy from previous row
                table[i][w] = table[i - 1][w];
                countTable[i][w] = countTable[i - 1][w];
                indexSumTable[i][w] = indexSumTable[i - 1][w];
            }
            else
            {
                // Item fits, check if including it improves the solution
                unsigned int valueWithItem = table[i - 1][w - weights[i - 1]] + profits[i - 1];
                unsigned int valueWithoutItem = table[i - 1][w];

                // Count with item would be count of previous solution + 1
                unsigned int countWithItem = countTable[i - 1][w - weights[i - 1]] + 1;

                // Index sum with item would be previous sum + current index
                unsigned int indexSumWithItem = indexSumTable[i - 1][w - weights[i - 1]] + (i - 1);

                // Decision logic with tiebreakers:
                // 1. Higher profit wins
                // 2. If profits are equal, fewer pallets wins
                // 3. If both are equal, lower index sum wins (prioritizing lower indices)

                if (valueWithItem > valueWithoutItem)
                {
                    // Clear win for including the item (higher profit)
                    table[i][w] = valueWithItem;
                    countTable[i][w] = countWithItem;
                    indexSumTable[i][w] = indexSumWithItem;
                }
                else if (valueWithItem == valueWithoutItem)
                {
                    // Tiebreaker 1: If profits are equal, prefer fewer pallets
                    if (countWithItem < countTable[i - 1][w])
                    {
                        table[i][w] = valueWithItem;
                        countTable[i][w] = countWithItem;
                        indexSumTable[i][w] = indexSumWithItem;
                    }
                    else if (countWithItem == countTable[i - 1][w])
                    {
                        // Tiebreaker 2: If pallet counts are also equal, prefer lower indices
                        if (indexSumWithItem < indexSumTable[i - 1][w])
                        {
                            table[i][w] = valueWithItem;
                            countTable[i][w] = countWithItem;
                            indexSumTable[i][w] = indexSumWithItem;
                        }
                        else
                        {
                            // Otherwise, don't include this item
                            table[i][w] = valueWithoutItem;
                            countTable[i][w] = countTable[i - 1][w];
                            indexSumTable[i][w] = indexSumTable[i - 1][w];
                        }
                    }
                    else
                    {
                        // More pallets than not including, so don't include
                        table[i][w] = valueWithoutItem;
                        countTable[i][w] = countTable[i - 1][w];
                        indexSumTable[i][w] = indexSumTable[i - 1][w];
                    }
                }
                else
                {
                    // Better not to include the item (lower profit)
                    table[i][w] = valueWithoutItem;
                    countTable[i][w] = countTable[i - 1][w];
                    indexSumTable[i][w] = indexSumTable[i - 1][w];
                }
            }
        }
    }

    // Complete progress bar if it was shown and user didn't cancel
    if (!user_cancelled)
    {
        progress.complete();
    }

    // If user cancelled, inform them and return 0
    if (user_cancelled)
    {
        std::cout << "\nOperation cancelled by user. Returning to menu." << std::endl;

        // Clear used items array to indicate cancellation
        for (unsigned int i = 0; i < n; i++)
        {
            usedItems[i] = false;
        }

        // No need to clear the tables since we're returning 0
        // and they won't be used again in this function call

        return 0;
    }

    // Backtracking to determine which items were used
    for (unsigned int i = 0; i < n; i++)
    {
        usedItems[i] = false;
    }

    unsigned int w = capacity;
    for (int i = n; i > 0; i--)
    {
        // Check if this item was included in our optimal solution
        // We need to check if any of our criteria changed, not just profit
        bool isIncluded = false;

        // If profit changed, or if profit stayed the same but count or index sum changed
        if (table[i][w] != table[i - 1][w] ||
            countTable[i][w] != countTable[i - 1][w] ||
            indexSumTable[i][w] != indexSumTable[i - 1][w])
        {

            // Check if including this item leads to the solution we chose
            if (w >= weights[i - 1] &&
                table[i][w] == table[i - 1][w - weights[i - 1]] + profits[i - 1] &&
                countTable[i][w] == countTable[i - 1][w - weights[i - 1]] + 1 &&
                indexSumTable[i][w] == indexSumTable[i - 1][w - weights[i - 1]] + (i - 1))
            {

                isIncluded = true;
            }
        }

        if (isIncluded)
        {
            usedItems[i - 1] = true;
            w -= weights[i - 1];
        }
    }

    // Return the maximum profit
    return table[n][capacity];
}