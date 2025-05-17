#ifndef MENU_H

#define MENU_H

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "../Approaches/Exhaustive.h"
#include "../InputOutput/Output.h"

/**
 * @file Menu.h
 * @brief Header file for the Truck Packing Optimization menu system
 */


/**
 * @brief Displays the main menu and gets user selection
 * @return Selected menu option (1-7)
 *
 * Menu options:
 * 1. Exhaustive Search Algorithm
 * 2. Dynamic Programming Approach
 * 3. Approximation Algorithm
 * 4. Linear Integer Programming
 * 5. Compare All Algorithms
 * 6. Info & Instructions
 * 7. Exit
 */
int optionsMenu();

/**
 * @brief Handles the selected menu option
 * @param option The selected menu option (1-7)
 * @param pallets Array of pallet IDs
 * @param weights Array of pallet weights
 * @param profits Array of pallet profits
 * @param n Number of pallets
 * @param capacity Truck's maximum weight capacity
 * @param max_pallets Maximum number of pallets allowed
 */
void handleMenuOption(int option, unsigned int pallets[], unsigned int weights[],
                     unsigned int profits[], unsigned int n,
                     int capacity, unsigned int max_pallets);
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
void optionShowInfoMenu(unsigned int pallets[], int capacity);


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
                           unsigned int capacity, unsigned int max_pallets);

#endif //MENU_H
