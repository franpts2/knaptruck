/**
 * @file Greedy.cpp
 * @brief Greedy approximation algorithms for pallet loading
 */

#include "Greedy.h"
#include "../InputOutput/ProgressBar.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>

/**
 * @brief Greedy approximation using weight-to-profit ratio
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @param max_pallets Maximum number of pallets allowed
 * @return GreedySol containing the solution
 */
GreedySol knapsackGreedyRatio(unsigned int profits[], unsigned int weights[],
                              unsigned int n, unsigned int max_weight)
{
    GreedySol solution;
    solution.total_profit = 0;
    solution.total_weight = 0;
    solution.pallet_count = 0;
    solution.used_pallets.resize(n, false);
    solution.approach_name = "Weight-to-Profit Ratio";

    // Create pairs of (index, profit/weight ratio)
    std::vector<std::pair<unsigned int, double>> items(n);
    for (unsigned int i = 0; i < n; i++)
    {
        // Avoid division by zero
        if (weights[i] == 0)
        {
            items[i] = std::make_pair(i, std::numeric_limits<double>::max());
        }
        else
        {
            // Calculate profit-to-weight ratio
            double ratio = static_cast<double>(profits[i]) / weights[i];
            items[i] = std::make_pair(i, ratio);
        }
    }

    // Sort items by profit-to-weight ratio in descending order
    std::sort(items.begin(), items.end(),
              [](const std::pair<unsigned int, double> &a,
                 const std::pair<unsigned int, double> &b)
              {
                  return a.second > b.second;
              });

    // Initialize progress bar
    ProgressBar progress(n);
    bool user_cancelled = false;

    // Greedy selection process
    for (unsigned int i = 0; i < n; i++)
    {
        // Update progress bar
        if (progress.shouldShow())
        {
            if (!progress.update(i))
            {
                user_cancelled = true;
                break;
            }
        }

        unsigned int idx = items[i].first;

        // Check if adding this item exceeds capacity or max pallets
        if (solution.total_weight + weights[idx] <= max_weight)
        {
            // Add item to solution
            solution.used_pallets[idx] = true;
            solution.total_profit += profits[idx];
            solution.total_weight += weights[idx];
            solution.pallet_count++;
        }
    }

    // Complete the progress bar if it was shown
    if (!user_cancelled)
    {
        progress.complete();
    }

    // If user cancelled, return an empty solution
    if (user_cancelled)
    {
        std::cout << "\nOperation cancelled by user. Returning to menu." << std::endl;

        // Clear the solution to indicate cancellation
        solution = {0, 0, 0, std::vector<bool>(n, false), "Weight-to-Profit Ratio (Cancelled)"};
    }

    return solution;
}

/**
 * @brief Greedy approximation using profit values
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @return GreedySol containing the solution
 */
GreedySol knapsackGreedyProfit(unsigned int profits[], unsigned int weights[],
                               unsigned int n, unsigned int max_weight)
{
    GreedySol solution;
    solution.total_profit = 0;
    solution.total_weight = 0;
    solution.pallet_count = 0;
    solution.used_pallets.resize(n, false);
    solution.approach_name = "Biggest Profit Values";

    // Create pairs of (index, profit)
    std::vector<std::pair<unsigned int, unsigned int>> items(n);
    for (unsigned int i = 0; i < n; i++)
    {
        items[i] = std::make_pair(i, profits[i]);
    }

    // Sort items by profit value in descending order
    std::sort(items.begin(), items.end(),
              [](const std::pair<unsigned int, unsigned int> &a,
                 const std::pair<unsigned int, unsigned int> &b)
              {
                  return a.second > b.second;
              });

    // Initialize progress bar
    ProgressBar progress(n);
    bool user_cancelled = false;

    // Greedy selection process - take items with highest profit first
    for (unsigned int i = 0; i < n; i++)
    {
        // Update progress bar
        if (progress.shouldShow())
        {
            if (!progress.update(i))
            {
                user_cancelled = true;
                break;
            }
        }

        unsigned int idx = items[i].first;

        // Check if adding this item exceeds capacity or max pallets
        if (solution.total_weight + weights[idx] <= max_weight)
        {
            // Add item to solution
            solution.used_pallets[idx] = true;
            solution.total_profit += profits[idx];
            solution.total_weight += weights[idx];
            solution.pallet_count++;
        }
    }

    // Complete the progress bar if it was shown
    if (!user_cancelled)
    {
        progress.complete();
    }

    // If user cancelled, return an empty solution
    if (user_cancelled)
    {
        std::cout << "\nOperation cancelled by user. Returning to menu." << std::endl;

        // Clear the solution to indicate cancellation
        solution = {0, 0, 0, std::vector<bool>(n, false), "Biggest Profit Values (Cancelled)"};
    }

    return solution;
}

/**
 * @brief Runs both greedy approximations and returns the better solution
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @return GreedySol containing the better solution
 */
GreedySol knapsackGreedyMaximum(unsigned int profits[], unsigned int weights[],
                                unsigned int n, unsigned int max_weight)
{
    std::cout << "Running Ratio-based Greedy algorithm...\n";
    // Run the ratio-based greedy algorithm
    GreedySol ratio_solution = knapsackGreedyRatio(profits, weights, n, max_weight);

    std::cout << "\nRunning Profit-based Greedy algorithm...\n";
    // Run the profit-based greedy algorithm
    GreedySol profit_solution = knapsackGreedyProfit(profits, weights, n, max_weight);

    // Compare the solutions and choose the better one
    if (ratio_solution.total_profit > profit_solution.total_profit)
    {
        ratio_solution.approach_name = "Maximum (Weight-to-Profit Ratio Selected)";
        return ratio_solution;
    }
    else if (profit_solution.total_profit > ratio_solution.total_profit)
    {
        profit_solution.approach_name = "Maximum (Biggest Profit Values Selected)";
        return profit_solution;
    }
    // Profits are equal, check pallet count
    if (ratio_solution.pallet_count < profit_solution.pallet_count)
    {
        ratio_solution.approach_name = "Maximum (Weight-to-Profit Ratio Selected)";
        return ratio_solution;
    }
    else if (profit_solution.pallet_count < ratio_solution.pallet_count)
    {
        profit_solution.approach_name = "Maximum (Biggest Profit Values Selected)";
        return profit_solution;
    }
    // Pallet counts are also equal, check total weight
    if (ratio_solution.total_weight <= profit_solution.total_weight)
    {
        ratio_solution.approach_name = "Maximum (Weight-to-Profit Ratio Selected)";
        return ratio_solution;
    }
    else
    {
        profit_solution.approach_name = "Maximum (Biggest Profit Values Selected)";
        return profit_solution;
    }
}