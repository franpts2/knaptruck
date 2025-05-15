/**
* @file Output.cpp
 * @brief Output handling for exhaustive search results
 */

#include "Output.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

void OutputExhaustiveSolution(unsigned int pallets[], unsigned int weights[],
                             unsigned int profits[], unsigned int n,
                             const BFSol &solution) {
    std::cout << "\n=========== EXHAUSTIVE SEARCH RESULTS ===========\n";
    std::cout << "Total profit: " << solution.total_profit << "\n";
    std::cout << "Total weight: " << solution.total_weight << " / "
              << (solution.total_weight > solution.total_profit ? "OVERLOAD!" : "OK") << "\n";
    std::cout << "Pallets used: " << solution.pallet_count << " / " << n << "\n\n";

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