#ifndef MENU_H

#define MENU_H

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

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
 * @tparam T Type parameter (for potential future templating)
 * @param option The selected menu option (1-7)
 * @param pallets Reference to vector of pallets to optimize
 * @param capacity Truck's maximum weight capacity
 */
template<class T>
void handleMenuOption(int option, std::vector<unsigned int>& pallets, int capacity);

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
void optionShowInfoMenu(std::vector<unsigned int>& pallets, int capacity);


#endif //MENU_H
