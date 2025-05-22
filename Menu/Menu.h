#ifndef MENU_H

#define MENU_H

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "../Approaches/Exhaustive.h"
#include "../Approaches/DynamicProgramming.h"  // Adding include for DynamicProgramming
#include "../Approaches/Backtracking.h"  // Adding include for Backtracking
#include "../Output/Output.h"


void mainMenu();
void datasetSelectionAndRun();

/**
 * @file Menu.h
 * @brief Header file for the Truck Packing Optimization menu system
 */


/**
 * @brief Displays the main menu and gets user selection
 * @return Selected menu option (1-8)
 *
 * Menu options:
 * 1. Exhaustive Search Algorithm
 * 2. Dynamic Programming Approach
 * 3. Backtracking Approach
 * 4. Approximation Algorithm
 * 5. Linear Integer Programming
 * 6. Compare All Algorithms
 * 7. Info & Instructions
 * 8. Exit
 */
int optionsMenu();

/**
 * @brief Handles the selected menu option
 * @param option The selected menu option (1-8)
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck's maximum weight capacity
 * @param max_pallets Maximum number of pallets allowed
 */
void handleMenuOption(int option, unsigned int pallets[], unsigned int weights[],
                     unsigned int profits[], unsigned int n,
                     int capacity);
/**
 * @brief Displays information about the program and input formats
 * @param pallets Reference to vector of pallets (maintains context)
 * @param capacity Truck's maximum weight capacity (maintains context)
 *
 * Shows:
 * - Batch mode instructions (file input)
 * - Interactive mode instructions (console input)
 * - Program usage examples
 */
void optionShowInfoMenu();


/**
 * @brief Handles the exhaustive search algorithm option
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck capacity
 * @param max_pallets Maximum number of pallets allowed
 */
void optionExhaustiveSearch(unsigned int pallets[], unsigned int weights[],
                           unsigned int profits[], unsigned int n,
                           unsigned int capacity);

/**
 * @brief Handles the dynamic programming algorithm option
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck capacity
 * @param max_pallets Maximum number of pallets allowed
 */
void optionDynamicProgramming(unsigned int pallets[], unsigned int weights[],
                             unsigned int profits[], unsigned int n,
                             unsigned int capacity);

/**
 * @brief Handles the backtracking algorithm option
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck capacity
 * @param max_pallets Maximum number of pallets allowed
 */
void optionBacktracking(unsigned int pallets[], unsigned int weights[],
                     unsigned int profits[], unsigned int n,
                     unsigned int capacity);

void optionLinearProgramming(unsigned int pallets[], unsigned int weights[],
                        unsigned int profits[], unsigned int n,
                        unsigned int capacity);

/**
 * @brief Allows the user to interactively input pallet data
 * 
 * Prompts the user for:
 * 1. Truck capacity (max weight)
 * 2. Number of pallets to enter
 * 3. Data for each pallet in format "palletID weight profit"
 * 
 * @return A pointer to an array containing [capacity, n, max_pallets, 
 *         followed by flattened arrays of pallets, weights, and profits]
 */
unsigned int* interactiveDataEntry();

int approximationSubmenu();

void optionGreedyRatio(unsigned int pallets[], unsigned int weights[],
                       unsigned int profits[], unsigned int n,
                       unsigned int capacity);

void optionGreedyProfit(unsigned int pallets[], unsigned int weights[],
                        unsigned int profits[], unsigned int n,
                        unsigned int capacity);

void optionGreedyMaximum(unsigned int pallets[], unsigned int weights[],
                         unsigned int profits[], unsigned int n,
                         unsigned int capacity);

#endif //MENU_H
