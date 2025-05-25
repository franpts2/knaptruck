#include "Greedy.h"
#include "../Output/ProgressBar.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>


GreedySol knapsackGreedyRatio(unsigned int profits[], unsigned int weights[],
                              unsigned int n, unsigned int max_weight)
{
    GreedySol solution;
    solution.total_profit = 0;
    solution.total_weight = 0;
    solution.pallet_count = 0;
    solution.used_pallets.resize(n, false);
    solution.approach_name = "Weight-to-Profit Ratio";

    std::vector<std::pair<unsigned int, double>> items(n);
    for (unsigned int i = 0; i < n; i++)
    {
        if (weights[i] == 0)
        {
            items[i] = std::make_pair(i, std::numeric_limits<double>::max());
        }
        else
        {
            double ratio = static_cast<double>(profits[i]) / weights[i];
            items[i] = std::make_pair(i, ratio);
        }
    }

    // sort items by profit/weight ratio in descending order
    // if ratios are equal, prioritize lower indices
    std::sort(items.begin(), items.end(),
              [](const std::pair<unsigned int, double> &a,
                 const std::pair<unsigned int, double> &b)
              {
                  if (a.second != b.second)
                      return a.second > b.second;
                  return a.first < b.first;
              });

    ProgressBar progress(n);
    bool user_cancelled = false;

    for (unsigned int i = 0; i < n; i++)
    {
        if (progress.shouldShow())
        {
            if (!progress.update(i))
            {
                user_cancelled = true;
                break;
            }
        }

        unsigned int idx = items[i].first;

        if (solution.total_weight + weights[idx] <= max_weight)
        {
            solution.used_pallets[idx] = true;
            solution.total_profit += profits[idx];
            solution.total_weight += weights[idx];
            solution.pallet_count++;
        }
    }

    if (!user_cancelled)
    {
        progress.complete();
    }

    if (user_cancelled)
    {
        std::cout << "\nOperation cancelled by user. Returning to menu." << std::endl;

        solution = {0, 0, 0, std::vector<bool>(n, false), "Weight-to-Profit Ratio (Cancelled)"};
    }

    return solution;
}

GreedySol knapsackGreedyProfit(unsigned int profits[], unsigned int weights[],
                               unsigned int n, unsigned int max_weight)
{
    GreedySol solution;
    solution.total_profit = 0;
    solution.total_weight = 0;
    solution.pallet_count = 0;
    solution.used_pallets.resize(n, false);
    solution.approach_name = "Biggest Profit Values";

    std::vector<std::pair<unsigned int, unsigned int>> items(n);
    for (unsigned int i = 0; i < n; i++)
    {
        items[i] = std::make_pair(i, profits[i]);
    }

    // sort items by profit value in descending order
    // if profits are equal, prioritize lower indices (tiebreaker)
    std::sort(items.begin(), items.end(),
              [](const std::pair<unsigned int, unsigned int> &a,
                 const std::pair<unsigned int, unsigned int> &b)
              {
                  if (a.second != b.second)
                      return a.second > b.second;
                  return a.first < b.first;
              });

    ProgressBar progress(n);
    bool user_cancelled = false;

    for (unsigned int i = 0; i < n; i++)
    {
        if (progress.shouldShow())
        {
            if (!progress.update(i))
            {
                user_cancelled = true;
                break;
            }
        }

        unsigned int idx = items[i].first;

        if (solution.total_weight + weights[idx] <= max_weight)
        {
            solution.used_pallets[idx] = true;
            solution.total_profit += profits[idx];
            solution.total_weight += weights[idx];
            solution.pallet_count++;
        }
    }

    if (!user_cancelled)
    {
        progress.complete();
    }

    if (user_cancelled)
    {
        std::cout << "\nOperation cancelled by user. Returning to menu." << std::endl;

        solution = {0, 0, 0, std::vector<bool>(n, false), "Biggest Profit Values (Cancelled)"};
    }

    return solution;
}

GreedySol knapsackGreedyMaximum(unsigned int profits[], unsigned int weights[],
                                unsigned int n, unsigned int max_weight)
{
    GreedySol ratio_solution = knapsackGreedyRatio(profits, weights, n, max_weight);

    GreedySol profit_solution = knapsackGreedyProfit(profits, weights, n, max_weight);

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

    // if profits are equal, check pallet count
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

    // if pallet counts are also equal, check total weight
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

