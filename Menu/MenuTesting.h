#ifndef MENUTESTING_H
#define MENUTESTING_H

#include <iostream>
#include <string>
#include "../Approaches/Exhaustive.h"
#include "../Approaches/DynamicProgramming.h"
#include "../Approaches/Backtracking.h"
#include "../ReadData/read.h"

/**
 * @brief Displays the algorithm selection menu and gets user choice
 * @return Selected algorithm number (1-3)
 */
int algorithmSelectionMenu();

/**
 * @brief Displays the dataset selection menu and gets user choice
 * @return Selected dataset number (1-10)
 */
int datasetSelectionMenu();

/**
 * @brief Loads the specified dataset and runs the brute force algorithm
 * @param datasetNumber The dataset number (1-10) chosen by the user
 * @return True if successful, false otherwise
 */
bool runBruteForceOnDataset(int datasetNumber);

/**
 * @brief Loads the specified dataset and runs the dynamic programming algorithm
 * @param datasetNumber The dataset number (1-10) chosen by the user
 * @return True if successful, false otherwise
 */
bool runDynamicProgrammingOnDataset(int datasetNumber);

/**
 * @brief Loads the specified dataset and runs the backtracking algorithm
 * @param datasetNumber The dataset number (1-10) chosen by the user
 * @return True if successful, false otherwise
 */
bool runBacktrackingOnDataset(int datasetNumber);

/**
 * @brief Gets the file path for the specified dataset number
 * @param datasetNumber The dataset number (1-10)
 * @param isPalletFile Whether to get the pallet file (true) or truck file (false)
 * @return The file path as a string
 */
std::string getDatasetPath(int datasetNumber, bool isPalletFile);

/**
 * @brief Test menu main function to run the testing interface
 * @return 0 on successful execution
 */
int runTestingMenu();

#endif // MENUTESTING_H