/**
* @file Output.cpp
* @brief Output handling for algorithm results
*/

#include "Output.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

void OutputExhaustiveSolution(unsigned int pallets[], unsigned int weights[],
                             unsigned int profits[], unsigned int n,
                             const BFSol &solution, double executionTime) {
    std::cout << "\n=========== EXHAUSTIVE SEARCH RESULTS ===========\n";
    std::cout << "Total profit: " << solution.total_profit << "\n";
    std::cout << "Total weight: " << solution.total_weight << " / "
              << (solution.total_weight > solution.total_profit ? "OVERLOAD!" : "OK") << "\n";
    std::cout << "Pallets used: " << solution.pallet_count << " / " << n << "\n";
    std::cout << "Execution time: " << std::fixed << std::setprecision(3) << executionTime << " ms\n\n";

    std::cout << "Selected pallets:\n";
    std::cout << std::setw(10) << "Pallet ID"
              << std::setw(10) << "Weight"
              << std::setw(10) << "Profit" << "\n";
    std::cout << "----------------------------------------\n";

    for (unsigned int i = 0; i < n; i++) {
        if (solution.used_pallets[i]) {
            std::cout << std::setw(10) << pallets[i]
                      << std::setw(10) << weights[i]
                      << std::setw(10) << profits[i] << "\n";
        }
    }

    std::cout << "\n================================================\n";

    // Option to return to menu
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.ignore();
    std::cin.get();
}

void OutputDynamicProgramming(unsigned int pallets[], unsigned int weights[],
                             unsigned int profits[], unsigned int n,
                             unsigned int totalProfit, unsigned int totalWeight, 
                             unsigned int palletCount, const bool usedItems[],
                             double executionTime) {
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

    for (unsigned int i = 0; i < n; i++) {
        if (usedItems[i]) {
            std::cout << std::setw(10) << pallets[i]
                      << std::setw(10) << weights[i]
                      << std::setw(10) << profits[i] << "\n";
        }
    }

    std::cout << "\n=================================================\n";

    // Option to return to menu
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.ignore();
    std::cin.get();
}

void OutputBacktracking(unsigned int pallets[], unsigned int weights[],
                       unsigned int profits[], unsigned int n,
                       const BTSol &solution, double executionTime) {
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

    for (unsigned int i = 0; i < n; i++) {
        if (solution.used_pallets[i]) {
            std::cout << std::setw(10) << pallets[i]
                      << std::setw(10) << weights[i]
                      << std::setw(10) << profits[i] << "\n";
        }
    }

    std::cout << "\n=================================================\n";

    // Option to return to menu
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.ignore();
    std::cin.get();
}