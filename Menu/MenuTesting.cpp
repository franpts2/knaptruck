#include "MenuTesting.h"
#include "../ReadData/read.h"
#include "../InputOutput/Output.h"
#include "../Approaches/Exhaustive.h"
#include "../Approaches/DynamicProgramming.h"
#include "../Approaches/Backtracking.h"
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>

// Enum for algorithm types
enum AlgorithmType
{
    BRUTE_FORCE = 1,
    DYNAMIC_PROGRAMMING = 2,
    BACKTRACKING = 3,
    APPROXIMATION = 4
};

// Struct for Dynamic Programming solution (added to match with BFSol)
struct DPSol
{
    unsigned int total_profit;
    unsigned int total_weight;
    unsigned int pallet_count;
    std::vector<bool> used_pallets;
};

// Struct for Greedy Approximation solution
// struct GreedySol
// {
//     unsigned int total_profit;
//     unsigned int total_weight;
//     unsigned int pallet_count;
//     std::vector<bool> used_pallets;
//     std::string approach_name; // To track which greedy approach was used
// };

int algorithmSelectionMenu()
{
    int choice;

    std::cout << "\n=====================================================" << std::endl;
    std::cout << "               ALGORITHM SELECTION MENU" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Please select an algorithm to test:" << std::endl;
    std::cout << "  1. Brute Force" << std::endl;
    std::cout << "  2. Dynamic Programming" << std::endl;
    std::cout << "  3. Backtracking" << std::endl;
    std::cout << "  4. Approximation Algorithm" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Enter your choice (1-4): ";

    // Input validation to ensure a number between 1-4 is entered
    do
    {
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > 4)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number between 1 and 4: ";
        }
        else
        {
            break;
        }
    } while (true);

    return choice;
}

int datasetSelectionMenu()
{
    int choice;

    std::cout << "\n=====================================================" << std::endl;
    std::cout << "                DATASET SELECTION MENU" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Please select a dataset number (1-10):" << std::endl;
    std::cout << "  Datasets 1-4:  Standard datasets" << std::endl;
    std::cout << "  Datasets 5-10: Extra datasets" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Enter dataset number (1-10): ";

    // Input validation to ensure a number between 1-10 is entered
    do
    {
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > 10)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number between 1 and 10: ";
        }
        else
        {
            break;
        }
    } while (true);

    return choice;
}

std::string getDatasetPath(int datasetNumber, bool isPalletFile)
{
    std::string basePath;
    std::string filePrefix = isPalletFile ? "Pallets_" : "TruckAndPallets_";
    std::string fileExtension = ".csv";

    // Using "../" to navigate up from the build directory to the project root
    std::string relativePrefix = "../";

    // Choose the correct directory based on dataset number
    if (datasetNumber >= 1 && datasetNumber <= 4)
    {
        basePath = "datasets/";
    }
    else if (datasetNumber >= 5 && datasetNumber <= 10)
    {
        basePath = "datasets-extra/";
    }
    else
    {
        return ""; // Invalid dataset number
    }

    // Format the dataset number with leading zero if necessary
    std::string formattedNumber = (datasetNumber < 10) ? "0" + std::to_string(datasetNumber) : std::to_string(datasetNumber);

    return relativePrefix + basePath + filePrefix + formattedNumber + fileExtension;
}

bool runBruteForceOnDataset(int datasetNumber)
{
    std::cout << "\nLoading dataset " << datasetNumber << "..." << std::endl;

    // Get file paths
    std::string truckFilePath = getDatasetPath(datasetNumber, false);
    std::string palletFilePath = getDatasetPath(datasetNumber, true);

    std::cout << "Using files:\n- " << palletFilePath << "\n- " << truckFilePath << std::endl;

    // Read truck capacity and number of pallets
    unsigned int trucksAndPallets[2];
    readTrucks(truckFilePath, trucksAndPallets);

    const unsigned int capacity = trucksAndPallets[0];
    const unsigned int n = trucksAndPallets[1];

    // Read pallets data
    unsigned int pallets[n];
    unsigned int weights[n];
    unsigned int profits[n];
    readPallets(palletFilePath, pallets, weights, profits);

    // Display dataset information
    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "Dataset #" << datasetNumber << " Information:" << std::endl;
    std::cout << "- Truck capacity: " << capacity << std::endl;
    std::cout << "- Number of pallets: " << n << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    std::cout << "\nPallets available:" << std::endl;
    std::cout << std::setw(10) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit" << std::endl;
    for (unsigned int i = 0; i < n; i++)
    {
        std::cout << std::setw(10) << pallets[i] << std::setw(10) << weights[i] << std::setw(10) << profits[i] << std::endl;
    }

    std::cout << "\nRunning brute force algorithm..." << std::endl;

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run the brute force algorithm
    BFSol solution = knapsackBF(profits, weights, n, capacity, n);

    // End timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "Brute Force Solution Results:" << std::endl;
    std::cout << "- Total profit: " << solution.total_profit << std::endl;
    std::cout << "- Total weight: " << solution.total_weight << std::endl;
    std::cout << "- Number of pallets used: " << solution.pallet_count << std::endl;
    std::cout << "- Execution time: " << duration.count() << " ms" << std::endl;

    // Display selected pallets
    std::cout << "\nSelected pallets:" << std::endl;
    std::cout << std::setw(10) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit" << std::endl;
    for (unsigned int i = 0; i < n; i++)
    {
        if (solution.used_pallets[i])
        {
            std::cout << std::setw(10) << pallets[i] << std::setw(10) << weights[i] << std::setw(10) << profits[i] << std::endl;
        }
    }

    return true;
}

// Wrapper function for the DP algorithm to match our UI structure
DPSol runDPAlgorithm(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity)
{
    DPSol solution;
    solution.used_pallets.resize(n);

    // Create a boolean array for the DP algorithm since std::vector<bool>::data() isn't accessible
    bool *usedItems = new bool[n]();

    // Call the actual DP algorithm implementation
    solution.total_profit = knapsackDP(profits, weights, n, capacity, usedItems);

    // Copy the results from the boolean array to our vector
    for (unsigned int i = 0; i < n; i++)
    {
        solution.used_pallets[i] = usedItems[i];
    }

    // Calculate total weight and pallet count based on used_pallets
    solution.total_weight = 0;
    solution.pallet_count = 0;

    for (unsigned int i = 0; i < n; i++)
    {
        if (solution.used_pallets[i])
        {
            solution.total_weight += weights[i];
            solution.pallet_count++;
        }
    }

    // Clean up
    delete[] usedItems;

    return solution;
}

bool runDynamicProgrammingOnDataset(int datasetNumber)
{
    std::cout << "\nLoading dataset " << datasetNumber << "..." << std::endl;

    // Get file paths
    std::string truckFilePath = getDatasetPath(datasetNumber, false);
    std::string palletFilePath = getDatasetPath(datasetNumber, true);

    std::cout << "Using files:\n- " << palletFilePath << "\n- " << truckFilePath << std::endl;

    // Read truck capacity and number of pallets
    unsigned int trucksAndPallets[2];
    readTrucks(truckFilePath, trucksAndPallets);

    const unsigned int capacity = trucksAndPallets[0];
    const unsigned int n = trucksAndPallets[1];

    // Read pallets data
    unsigned int pallets[n];
    unsigned int weights[n];
    unsigned int profits[n];
    readPallets(palletFilePath, pallets, weights, profits);

    // Display dataset information
    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "Dataset #" << datasetNumber << " Information:" << std::endl;
    std::cout << "- Truck capacity: " << capacity << std::endl;
    std::cout << "- Number of pallets: " << n << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    std::cout << "\nPallets available:" << std::endl;
    std::cout << std::setw(10) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit" << std::endl;
    for (unsigned int i = 0; i < n; i++)
    {
        std::cout << std::setw(10) << pallets[i] << std::setw(10) << weights[i] << std::setw(10) << profits[i] << std::endl;
    }

    std::cout << "\nRunning dynamic programming algorithm..." << std::endl;

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run the dynamic programming algorithm
    DPSol solution = runDPAlgorithm(profits, weights, n, capacity);

    // End timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "Dynamic Programming Solution Results:" << std::endl;
    std::cout << "- Total profit: " << solution.total_profit << std::endl;
    std::cout << "- Total weight: " << solution.total_weight << std::endl;
    std::cout << "- Number of pallets used: " << solution.pallet_count << std::endl;
    std::cout << "- Execution time: " << duration.count() << " ms" << std::endl;

    // Display selected pallets
    std::cout << "\nSelected pallets:" << std::endl;
    std::cout << std::setw(10) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit" << std::endl;
    for (unsigned int i = 0; i < n; i++)
    {
        if (solution.used_pallets[i])
        {
            std::cout << std::setw(10) << pallets[i] << std::setw(10) << weights[i] << std::setw(10) << profits[i] << std::endl;
        }
    }

    return true;
}

bool runBacktrackingOnDataset(int datasetNumber)
{
    std::cout << "\nLoading dataset " << datasetNumber << "..." << std::endl;

    // Get file paths
    std::string truckFilePath = getDatasetPath(datasetNumber, false);
    std::string palletFilePath = getDatasetPath(datasetNumber, true);

    std::cout << "Using files:\n- " << palletFilePath << "\n- " << truckFilePath << std::endl;

    // Read truck capacity and number of pallets
    unsigned int trucksAndPallets[2];
    readTrucks(truckFilePath, trucksAndPallets);

    const unsigned int capacity = trucksAndPallets[0];
    const unsigned int n = trucksAndPallets[1];

    // Read pallets data
    unsigned int pallets[n];
    unsigned int weights[n];
    unsigned int profits[n];
    readPallets(palletFilePath, pallets, weights, profits);

    // Display dataset information
    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "Dataset #" << datasetNumber << " Information:" << std::endl;
    std::cout << "- Truck capacity: " << capacity << std::endl;
    std::cout << "- Number of pallets: " << n << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    std::cout << "\nPallets available:" << std::endl;
    std::cout << std::setw(10) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit" << std::endl;
    for (unsigned int i = 0; i < n; i++)
    {
        std::cout << std::setw(10) << pallets[i] << std::setw(10) << weights[i] << std::setw(10) << profits[i] << std::endl;
    }

    std::cout << "\nRunning backtracking algorithm..." << std::endl;

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run the backtracking algorithm
    BTSol solution = knapsackBT(profits, weights, n, capacity, n);

    // End timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "Backtracking Solution Results:" << std::endl;
    std::cout << "- Total profit: " << solution.total_profit << std::endl;
    std::cout << "- Total weight: " << solution.total_weight << std::endl;
    std::cout << "- Number of pallets used: " << solution.pallet_count << std::endl;
    std::cout << "- Execution time: " << duration.count() << " ms" << std::endl;

    // Display selected pallets
    std::cout << "\nSelected pallets:" << std::endl;
    std::cout << std::setw(10) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit" << std::endl;
    for (unsigned int i = 0; i < n; i++)
    {
        if (solution.used_pallets[i])
        {
            std::cout << std::setw(10) << pallets[i] << std::setw(10) << weights[i] << std::setw(10) << profits[i] << std::endl;
        }
    }

    return true;
}

// Wrapper functions for different greedy algorithms
GreedySol runGreedyRatio(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, unsigned int max_pallets)
{
    return knapsackGreedyRatio(profits, weights, n, capacity, max_pallets);
}

GreedySol runGreedyProfit(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, unsigned int max_pallets)
{
    // return knapsackGreedyProfit(profits, weights, n, capacity, max_pallets);
}

GreedySol runGreedyMaximum(unsigned int profits[], unsigned int weights[], unsigned int n, unsigned int capacity, unsigned int max_pallets)
{
    // return knapsackGreedyMaximum(profits, weights, n, capacity, max_pallets);
}

bool runApproximationOnDataset(int datasetNumber)
{
    std::cout << "\nLoading dataset " << datasetNumber << "..." << std::endl;

    // Get file paths
    std::string truckFilePath = getDatasetPath(datasetNumber, false);
    std::string palletFilePath = getDatasetPath(datasetNumber, true);

    std::cout << "Using files:\n- " << palletFilePath << "\n- " << truckFilePath << std::endl;

    // Read truck capacity and number of pallets
    unsigned int trucksAndPallets[2];
    readTrucks(truckFilePath, trucksAndPallets);

    const unsigned int capacity = trucksAndPallets[0];
    const unsigned int n = trucksAndPallets[1];

    // Read pallets data
    unsigned int pallets[n];
    unsigned int weights[n];
    unsigned int profits[n];
    readPallets(palletFilePath, pallets, weights, profits);

    // Display dataset information
    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "Dataset #" << datasetNumber << " Information:" << std::endl;
    std::cout << "- Truck capacity: " << capacity << std::endl;
    std::cout << "- Number of pallets: " << n << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    std::cout << "\nPallets available:" << std::endl;
    std::cout << std::setw(10) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit" << std::endl;
    for (unsigned int i = 0; i < n; i++)
    {
        std::cout << std::setw(10) << pallets[i] << std::setw(10) << weights[i] << std::setw(10) << profits[i] << std::endl;
    }

    // Get approximation submenu choice
    int approxChoice = approximationSubmenuTesting();

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run the selected approximation algorithm
    GreedySol solution;

    switch (approxChoice)
    {
    case 1:
        std::cout << "\nRunning Greedy Algorithm (Weight-to-Profit Ratio)..." << std::endl;
        solution = runGreedyRatio(profits, weights, n, capacity, n);
        break;
    case 2:
        std::cout << "\nRunning Greedy Algorithm (Biggest Profit Values)..." << std::endl;
        solution = runGreedyProfit(profits, weights, n, capacity, n);
        break;
    case 3:
        std::cout << "\nRunning Both Greedy Algorithms and Taking Maximum..." << std::endl;
        solution = runGreedyMaximum(profits, weights, n, capacity, n);
        break;
    }

    // End timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "Approximation Algorithm (" << solution.approach_name << ") Results:" << std::endl;
    std::cout << "- Total profit: " << solution.total_profit << std::endl;
    std::cout << "- Total weight: " << solution.total_weight << std::endl;
    std::cout << "- Number of pallets used: " << solution.pallet_count << std::endl;
    std::cout << "- Execution time: " << duration.count() << " ms" << std::endl;

    // Display selected pallets
    std::cout << "\nSelected pallets:" << std::endl;
    std::cout << std::setw(10) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit" << std::endl;
    for (unsigned int i = 0; i < n; i++)
    {
        if (solution.used_pallets[i])
        {
            std::cout << std::setw(10) << pallets[i] << std::setw(10) << weights[i] << std::setw(10) << profits[i] << std::endl;
        }
    }

    return true;
}

int approximationSubmenuTesting()
{
    int choice;

    std::cout << "\n=====================================================" << std::endl;
    std::cout << "          APPROXIMATION ALGORITHM OPTIONS" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Please select a greedy approach:" << std::endl;
    std::cout << "  1. Greedy A (Weight-to-Profit Ratio)" << std::endl;
    std::cout << "  2. Greedy B (Biggest Profit Values)" << std::endl;
    std::cout << "  3. Maximum of Both Approaches" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Enter your choice (1-3): ";

    // Input validation to ensure a number between 1-3 is entered
    do
    {
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > 3)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number between 1 and 3: ";
        }
        else
        {
            break;
        }
    } while (true);

    return choice;
}

int runTestingMenu()
{
    bool continueRunning = true;
    char choice;

    while (continueRunning)
    {
        // Display algorithm selection menu
        int algorithmChoice = algorithmSelectionMenu();

        // Display dataset selection menu and get dataset selection
        int datasetNumber = datasetSelectionMenu();

        bool success = false;

        // Run the selected algorithm on the chosen dataset
        if (algorithmChoice == BRUTE_FORCE)
        {
            success = runBruteForceOnDataset(datasetNumber);
        }
        else if (algorithmChoice == DYNAMIC_PROGRAMMING)
        {
            success = runDynamicProgrammingOnDataset(datasetNumber);
        }
        else if (algorithmChoice == BACKTRACKING)
        {
            success = runBacktrackingOnDataset(datasetNumber);
        }
        else if (algorithmChoice == APPROXIMATION)
        {
            success = runApproximationOnDataset(datasetNumber);
        }

        if (!success)
        {
            std::cout << "Error processing dataset " << datasetNumber << ". Please try again." << std::endl;
        }

        // Ask if the user wants to continue testing
        std::cout << "\nDo you want to test another dataset? (y/n): ";
        std::cin >> choice;

        if (choice != 'y' && choice != 'Y')
        {
            continueRunning = false;
        }
    }

    std::cout << "\nThank you for testing the algorithms!" << std::endl;
    return 0;
}