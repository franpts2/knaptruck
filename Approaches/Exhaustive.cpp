/**
 * @file Exhaustive.cpp
 * @brief Brute-force pallet loading implementation
 */

#include "Exhaustive.h"
#include "../InputOutput/ProgressBar.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>

/**
 * @brief Brute-force pallet loading algorithm
 * @param profits Array of profit values for each pallet
 * @param weights Array of weight values for each pallet
 * @param n Number of pallets
 * @param max_weight Maximum weight capacity of truck
 * @param max_pallets Maximum number of pallets allowed
 * @return BFSol containing optimal loading
 */
BFSol knapsackBF(unsigned int profits[], unsigned int weights[],
                                      unsigned int n, unsigned int max_weight,
                                      unsigned int max_pallets) {
    BFSol best_solution = {0, 0, 0, std::vector<bool>(n, false)};
    std::vector<bool> current(n, false);

    // Calculate total number of iterations (2^n)
    unsigned long long total_iterations = 1ULL << n; 
    
    // Initialize progress bar
    ProgressBar progress(total_iterations);
    unsigned long long iteration_count = 0;
    bool user_cancelled = false;

    // Generate all possible subsets (2^n possibilities)
    while (true) {
        // Update progress bar every 1000 iterations to reduce overhead
        if (iteration_count % 1000 == 0) {
            // Update returns false if user pressed escape
            if (progress.shouldShow()) {
                if (!progress.update(iteration_count)) {
                    user_cancelled = true;
                    break;
                }
            }
        }
        iteration_count++;

        // Calculate current subset's properties
        unsigned int current_weight = 0;
        unsigned int current_profit = 0;
        unsigned int current_count = 0;

        for (unsigned int i = 0; i < n; i++) {
            if (current[i]) {
                current_weight += weights[i];
                current_profit += profits[i];
                current_count++;
            }
        }

        // Check if this is a valid and better solution
        if (current_weight <= max_weight && current_count <= max_pallets) {

            if (current_profit > best_solution.total_profit ||
               (current_profit == best_solution.total_profit &&
                current_weight < best_solution.total_weight)) {

                best_solution.total_profit = current_profit;
                best_solution.total_weight = current_weight;
                best_solution.pallet_count = current_count;
                best_solution.used_pallets = current;
            }
        }

        // Generate next subset (binary counter increment)
        unsigned int i = 0;
        while (i < n && current[i]) {
            current[i] = false;
            i++;
        }

        if (i == n) break; // All combinations tried

        current[i] = true;
    }

    // Complete the progress bar if it was shown
    if (!user_cancelled) {
        progress.complete();
    }
    
    // If user cancelled, return an empty solution
    if (user_cancelled) {
        std::cout << "\nOperation cancelled by user. Returning to menu." << std::endl;
        
        // Clear the best solution to indicate cancellation
        best_solution = {0, 0, 0, std::vector<bool>(n, false)};
    }

    return best_solution;
}