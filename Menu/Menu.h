/**
 * @file Menu.h
 * @brief Header file for the Truck Packing Optimization menu system
 */

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "../Approaches/Exhaustive.h"
#include "../Approaches/DynamicProgramming.h"
#include "../Approaches/Backtracking.h"
#include "../Approaches/Greedy.h"
#include "../Output/Output.h"

/**
 * @brief Entry point of the menu system
 *
 * Initializes the main menu interface and handles high-level program flow
 * 
 * Main Menu options:
 * 1. Enter pallet data interactively
 * 2. Use predefined dataset
 * 3: Info & Instructions
 * 4. Exit
 */
void mainMenu();

/**
 * @brief Handles dataset selection and algorithm execution
 *
 * Guides users through selecting datasets and runs the selected algorithm
 */
void datasetSelectionAndRun();

/**
 * @brief Displays the algorithms menu and gets user selection
 * @return Selected menu option (1-8)
 *
 * Algorithms Menu options:
 * 1. Exhaustive Search Algorithm
 * 2. Dynamic Programming Approach
 * 3. Backtracking Approach
 * 4. Approximation Algorithm
 * 5. Linear Integer Programming
 * 6. Compare All Algorithms
 * 7. Change Input Data
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
 */
void handleMenuOption(int option, unsigned int pallets[], unsigned int weights[],
                      unsigned int profits[], unsigned int n,
                      int capacity);


/**
 * @brief Displays information about the program and input formats
 *
 * 1. For Predefined Dataset
 * 2. For Interactive Data Entry
 */
void optionShowInfoMenu();

/**
 * @brief Handles the exhaustive search algorithm option
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck capacity
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
 */
void optionBacktracking(unsigned int pallets[], unsigned int weights[],
                        unsigned int profits[], unsigned int n,
                        unsigned int capacity);

/**
 * @brief Handles the integer linear programming algorithm option
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck capacity
 */
void optionIntegerLinearProgramming(unsigned int pallets[], unsigned int weights[],
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
unsigned int *interactiveDataEntry();

/**
 * @brief Displays the approximation algorithm submenu
 * @return Selected submenu option
 *
 * Submenu options:
 * 1. Weight-to-Profit Ratio Greedy Approach
 * 2. Profit-First Greedy Approach
 * 3. Maximum of Both Greedy Approaches
 * 4. Return to Main Menu
 */
int approximationSubmenu();

/**
 * @brief Handles the weight-to-profit ratio greedy algorithm option
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck capacity
 */
void optionGreedyRatio(unsigned int pallets[], unsigned int weights[],
                       unsigned int profits[], unsigned int n,
                       unsigned int capacity);

/**
 * @brief Handles the profit-first greedy algorithm option
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck capacity
 */
void optionGreedyProfit(unsigned int pallets[], unsigned int weights[],
                        unsigned int profits[], unsigned int n,
                        unsigned int capacity);

/**
 * @brief Handles the maximum of both greedy algorithms option
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck capacity
 */
void optionGreedyMaximum(unsigned int pallets[], unsigned int weights[],
                         unsigned int profits[], unsigned int n,
                         unsigned int capacity);

/**
 * @brief Compares all implemented algorithms and shows performance metrics
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck capacity
 *
 * Runs each algorithm on the same dataset and displays:
 * - Execution time
 * - Total profit achieved
 * - Solution quality comparison
 */
void optionCompareAllAlgorithms(unsigned int pallets[], unsigned int weights[],
                                unsigned int profits[], unsigned int n,
                                unsigned int capacity);

#endif // MENU_H
