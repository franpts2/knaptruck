#include "DynamicProgramming.h"
#include "../Output/ProgressBar.h"
#include <vector>
#include <iostream>

unsigned int knapsackDP(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, bool usedItems[])
{
    std::vector<std::vector<unsigned int>> table(n + 1, std::vector<unsigned int>(capacity + 1, 0));

    // stores the number of pallets used for each solution
    std::vector<std::vector<unsigned int>> countTable(n + 1, std::vector<unsigned int>(capacity + 1, 0));

    // stores a score based on indices of pallets used 
    std::vector<std::vector<unsigned int>> indexSumTable(n + 1, std::vector<unsigned int>(capacity + 1, 0));

    unsigned long long total_operations = (unsigned long long)(n)*capacity;
    ProgressBar progress(total_operations);
    unsigned long long current_operation = 0;
    bool user_cancelled = false;

    for (unsigned int i = 1; i <= n && !user_cancelled; i++)
    {
        for (unsigned int w = 1; w <= capacity && !user_cancelled; w++)
        {
            current_operation++;

            if (current_operation % 10000 == 0)
            {
                if (progress.shouldShow())
                {
                    if (!progress.update(current_operation))
                    {
                        user_cancelled = true;
                        break;
                    }
                }
            }

            if (weights[i - 1] > w)
            {
                // item doesn't fit, copy from previous row
                table[i][w] = table[i - 1][w];
                countTable[i][w] = countTable[i - 1][w];
                indexSumTable[i][w] = indexSumTable[i - 1][w];
            }
            else
            {
                // item fits, check if including it improves the solution
                unsigned int valueWithItem = table[i - 1][w - weights[i - 1]] + profits[i - 1];
                unsigned int valueWithoutItem = table[i - 1][w];

                unsigned int countWithItem = countTable[i - 1][w - weights[i - 1]] + 1;

                unsigned int indexSumWithItem = indexSumTable[i - 1][w - weights[i - 1]] + (i - 1);

                if (valueWithItem > valueWithoutItem)
                {
                    table[i][w] = valueWithItem;
                    countTable[i][w] = countWithItem;
                    indexSumTable[i][w] = indexSumWithItem;
                }
                else if (valueWithItem == valueWithoutItem)
                {
                    if (countWithItem < countTable[i - 1][w])
                    {
                        table[i][w] = valueWithItem;
                        countTable[i][w] = countWithItem;
                        indexSumTable[i][w] = indexSumWithItem;
                    }
                    else if (countWithItem == countTable[i - 1][w])
                    {
                        if (indexSumWithItem < indexSumTable[i - 1][w])
                        {
                            table[i][w] = valueWithItem;
                            countTable[i][w] = countWithItem;
                            indexSumTable[i][w] = indexSumWithItem;
                        }
                        else
                        {
                            table[i][w] = valueWithoutItem;
                            countTable[i][w] = countTable[i - 1][w];
                            indexSumTable[i][w] = indexSumTable[i - 1][w];
                        }
                    }
                    else
                    {
                        table[i][w] = valueWithoutItem;
                        countTable[i][w] = countTable[i - 1][w];
                        indexSumTable[i][w] = indexSumTable[i - 1][w];
                    }
                }
                else
                {
                    table[i][w] = valueWithoutItem;
                    countTable[i][w] = countTable[i - 1][w];
                    indexSumTable[i][w] = indexSumTable[i - 1][w];
                }
            }
        }
    }

    if (!user_cancelled)
    {
        progress.complete();
    }

    if (user_cancelled)
    {
        std::cout << "\nOperation cancelled by user. Returning to menu." << std::endl;

        for (unsigned int i = 0; i < n; i++)
        {
            usedItems[i] = false;
        }

        return 0;
    }

    // backtracking to determine which items were used
    for (unsigned int i = 0; i < n; i++)
    {
        usedItems[i] = false;
    }

    unsigned int w = capacity;
    for (int i = n; i > 0; i--)
    {
        bool isIncluded = false;

        if (table[i][w] != table[i - 1][w] ||
            countTable[i][w] != countTable[i - 1][w] ||
            indexSumTable[i][w] != indexSumTable[i - 1][w])
        {

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

    return table[n][capacity];
}