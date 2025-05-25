/**
 * @file Output.cpp
 * @brief Output handling for algorithm results
 */

#include "Output.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <limits>

void OutputExhaustiveSolution(unsigned int pallets[], unsigned int weights[],
                              unsigned int profits[], unsigned int n,
                              const BFSol &solution, double executionTime)
{
    std::cout << "\n=========== EXHAUSTIVE SEARCH RESULTS ===========\n";
    std::cout << "Total profit: " << solution.total_profit << "\n";
    std::cout << "Total weight: " << solution.total_weight << "\n";
    std::cout << "Pallets used: " << solution.pallet_count << " / " << n << "\n";
    std::cout << "Execution time: " << std::fixed << std::setprecision(3) << executionTime << " ms\n\n";

    std::cout << "Selected pallets:\n";
    std::cout << std::setw(10) << "Pallet ID"
              << std::setw(10) << "Weight"
              << std::setw(10) << "Profit" << "\n";
    std::cout << "----------------------------------------\n";

    for (unsigned int i = 0; i < n; i++)
    {
        if (solution.used_pallets[i])
        {
            std::cout << std::setw(10) << pallets[i]
                      << std::setw(10) << weights[i]
                      << std::setw(10) << profits[i] << "\n";
        }
    }

    std::cout << "================================================\n";

    // Option to return to menu
    std::cout << "\nPress Enter to return to the algorithms menu...";
    std::cin.ignore();
    std::cin.get();
}

void OutputDynamicProgramming(unsigned int pallets[], unsigned int weights[],
                              unsigned int profits[], unsigned int n,
                              unsigned int totalProfit, unsigned int totalWeight,
                              unsigned int palletCount, const bool usedItems[],
                              double executionTime)
{
    std::cout << "\n=========== DYNAMIC PROGRAMMING RESULTS ===========\n";
    std::cout << "Total profit: " << totalProfit << "\n";
    std::cout << "Total weight: " << totalWeight << "\n";
    std::cout << "Pallets used: " << palletCount << " / " << n << "\n";
    std::cout << "Execution time: " << std::fixed << std::setprecision(3) << executionTime << " ms\n\n";

    std::cout << "Selected pallets:\n";
    std::cout << std::setw(10) << "Pallet ID"
              << std::setw(10) << "Weight"
              << std::setw(10) << "Profit" << "\n";
    std::cout << "----------------------------------------\n";

    for (unsigned int i = 0; i < n; i++)
    {
        if (usedItems[i])
        {
            std::cout << std::setw(10) << pallets[i]
                      << std::setw(10) << weights[i]
                      << std::setw(10) << profits[i] << "\n";
        }
    }

    std::cout << "=================================================\n";

    // Option to return to menu
    std::cout << "\nPress Enter to return to the algorithms menu...";
    std::cin.ignore();
    std::cin.get();
}

void OutputBacktracking(unsigned int pallets[], unsigned int weights[],
                        unsigned int profits[], unsigned int n,
                        const BTSol &solution, double executionTime)
{
    std::cout << "\n=========== BACKTRACKING RESULTS ===========\n";
    std::cout << "Total profit: " << solution.total_profit << "\n";
    std::cout << "Total weight: " << solution.total_weight << "\n";
    std::cout << "Pallets used: " << solution.pallet_count << " / " << n << "\n";
    std::cout << "Execution time: " << std::fixed << std::setprecision(3) << executionTime << " ms\n\n";

    std::cout << "Selected pallets:\n";
    std::cout << std::setw(10) << "Pallet ID"
              << std::setw(10) << "Weight"
              << std::setw(10) << "Profit" << "\n";
    std::cout << "----------------------------------------\n";

    for (unsigned int i = 0; i < n; i++)
    {
        if (solution.used_pallets[i])
        {
            std::cout << std::setw(10) << pallets[i]
                      << std::setw(10) << weights[i]
                      << std::setw(10) << profits[i] << "\n";
        }
    }

    std::cout << "==========================================\n";

    // Option to return to menu
    std::cout << "\nPress Enter to return to the algorithms menu...";
    std::cin.ignore();
    std::cin.get();
}

void OutputGreedyApproximation(unsigned int pallets[], unsigned int weights[],
                               unsigned int profits[], unsigned int n,
                               const GreedySol &solution, double executionTime)
{
    std::cout << "\n========== GREEDY APPROXIMATION RESULTS ==========\n";
    std::cout << "Algorithm: " << solution.approach_name << "\n";
    std::cout << "Total profit: " << solution.total_profit << "\n";
    std::cout << "Total weight: " << solution.total_weight << "\n";
    std::cout << "Pallets used: " << solution.pallet_count << " / " << n << "\n";
    std::cout << "Execution time: " << std::fixed << std::setprecision(3) << executionTime << " ms\n\n";

    std::cout << "Selected pallets:\n";
    std::cout << std::setw(10) << "Pallet ID"
              << std::setw(10) << "Weight"
              << std::setw(10) << "Profit\n";
    std::cout << "----------------------------------------\n";

    for (unsigned int i = 0; i < n; i++)
    {
        if (solution.used_pallets[i])
        {
            std::cout << std::setw(10) << pallets[i]
                      << std::setw(10) << weights[i]
                      << std::setw(10) << profits[i] << "\n";
        }
    }

    std::cout << "==========================================\n";

    // Option to return to menu
    std::cout << "\nPress Enter to return to the algorithms menu...";
    std::cin.ignore();
    std::cin.get();
}

void OutputIntegerLinearProgramming(unsigned int pallets[], unsigned int weights[],
                            unsigned int profits[], unsigned int n,
                            unsigned int capacity, int totalProfit, int totalWeight,
                            const std::vector<int>& selectedIndices, double executionTime)
{
    std::cout << "\n=========== INTEGER LINEAR PROGRAMMING RESULTS ===========\n";
    std::cout << "Total profit: " << totalProfit << "\n";
    std::cout << "Total weight: " << totalWeight << " / " << capacity << "\n";
    std::cout << "Pallets used: " << selectedIndices.size() << " / " << n << "\n";
    std::cout << "Execution time: " << std::fixed << std::setprecision(3) << executionTime << " ms\n\n";

    std::cout << "Selected pallets:\n";
    std::cout << std::setw(10) << "Pallet ID"
              << std::setw(10) << "Weight"
              << std::setw(10) << "Profit" << "\n";
    std::cout << "----------------------------------------\n";

    for (int index : selectedIndices) {
        std::cout << std::setw(10) << pallets[index] 
                  << std::setw(10) << weights[index] 
                  << std::setw(10) << profits[index] << "\n";
    }

    std::cout << "===========================================================\n";

    // Option to return to menu
    std::cout << "\nPress Enter to return to the algorithms menu...";
    std::cin.ignore();
    std::cin.get();
}

void OutputCompareAllAlgorithms(const std::vector<std::string>& names, 
                                const std::vector<double>& times, 
                                const std::vector<std::string>& spaceComplexities, 
                                const std::vector<std::string>& accuracyAlgorithms,
                                const std::vector<unsigned int>& profits) {
    double maxTime = *std::max_element(times.begin(), times.end());
    unsigned int maxProfit = *std::max_element(profits.begin(), profits.end());
    int chartWidth = 40;
    std::cout << "\nAlgorithm Performance Comparison:\n";
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "Algorithm           | Time (ms) | Profit | Space Complexity | Accuracy(%) \n";
    std::cout << "-------------------------------------------------------------------------\n";
    for (size_t i = 0; i < names.size(); ++i) {
        int barLen = maxTime > 0 ? static_cast<int>((times[i] / maxTime) * chartWidth) : 0;
        
        // Highlight the best profit value
        std::string profitStr = std::to_string(profits[i]);
        if (profits[i] == maxProfit && maxProfit > 0) {
            profitStr += " *"; // Mark best profit with an asterisk
        }
        
        // Calculate accuracy percentage
        double accuracyPercent = maxProfit > 0 ? 
            static_cast<double>(profits[i]) / maxProfit * 100.0 : 0.0;
        
        std::cout << std::left << std::setw(20) << names[i]
                  << "| " << std::setw(9) << std::fixed << std::setprecision(3) << times[i]
                  << "| " << std::setw(7) << profitStr
                  << "| " << std::setw(17) << spaceComplexities[i]
                  << "| " << std::setw(10) << std::fixed << std::setprecision(1) << accuracyPercent;
        std::cout << "\n";
    }
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "* Indicates optimal profit\n";
    std::cout << "Accuracy: algorithm profit / optimal profit × 100\n";
    std::cout << "\nPress Enter to return to the algorithms menu...";
    std::cin.ignore();
    std::cin.get();
}

