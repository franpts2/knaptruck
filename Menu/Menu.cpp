#include "Menu.h"
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>                // For std::setw
#include <limits>                 // For std::numeric_limits
#include "../Approaches/Greedy.h" // Add Greedy.h include
#include "../ReadData/read.h"

using namespace std;

// Unified entry point for the menu system
void mainMenu()
{
    while (true)
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << "         TRUCK PACKING MENU" << endl;
        cout << "========================================" << endl;
        cout << "1. Enter pallet data interactively" << endl;
        cout << "2. Use predefined dataset" << endl;
        cout << "3: Info & Instructions" << endl;
        cout << "4. Exit" << endl;
        cout << "Option: ";
        int mainChoice;
        cin >> mainChoice;
        if (mainChoice == 1)
        {
            unsigned int *data = interactiveDataEntry();
            unsigned int capacity = data[0];
            unsigned int n = data[1];
            // unsigned int max_pallets = data[2];
            unsigned int *pallets = &data[3];
            unsigned int *weights = &data[3 + n];
            unsigned int *profits = &data[3 + 2 * n];
            int option = optionsMenu();
            handleMenuOption(option, pallets, weights, profits, n, capacity);
            delete[] data;
        }
        else if (mainChoice == 2)
        {
            datasetSelectionAndRun();
        }
        else if (mainChoice == 3)
        {
            optionShowInfoMenu();
        }
        else if (mainChoice == 4)
        {
            cout << "Exiting..." << endl;
            exit(0);
        }
        else
        {
            cout << "Invalid input. Please choose 1-3." << endl;
        }
    }
}

int optionsMenu()
{
    cout << endl
         << "Loading options..." << endl;
    cout.flush();
    this_thread::sleep_for(chrono::seconds(1));

    cout << "==============================================" << endl;
    cout << "     TRUCK PACKING OPTIMIZATION ALGORITHMS    " << endl;
    cout << "==============================================" << endl
         << endl;

    int i;
    do
    {
        cout << "1: Exhaustive Search Algorithm" << endl;
        cout << "2: Dynamic Programming Approach" << endl;
        cout << "3: Backtracking Approach" << endl;
        cout << "4: Approximation Algorithm (Greedy Approach)" << endl;
        cout << "5: Linear Integer Programming" << endl;
        cout << "6: Compare All Algorithms" << endl;
        cout << "7: Change Input Data" << endl;
        cout << "8: Exit" << endl;
        cout << "Option: ";
        cin >> i;
        cout << endl;

        if (i < 1 || i > 8)
            cout << "Invalid input. Please choose 1-9." << endl;
    } while (i < 1 || i > 8);

    return i;
}

void handleMenuOption(int option, unsigned int pallets[], unsigned int weights[],
                      unsigned int profits[], unsigned int n,
                      int capacity)
{
    switch (option)
    {
    case 1:
        optionExhaustiveSearch(pallets, weights, profits, n, capacity);
        break;
    case 2:
        optionDynamicProgramming(pallets, weights, profits, n, capacity);
        break;
    case 3:
        optionBacktracking(pallets, weights, profits, n, capacity);
        break;
    case 4:
    {
        int subOption = approximationSubmenu();
        switch (subOption)
        {
        case 1:
            optionGreedyRatio(pallets, weights, profits, n, capacity);
            break;
        case 2:
            optionGreedyProfit(pallets, weights, profits, n, capacity);
            break;
        case 3:
            optionGreedyMaximum(pallets, weights, profits, n, capacity);
            break;
        case 4:
            // Return to main menu
            {
                int next_option = optionsMenu();
                handleMenuOption(next_option, pallets, weights, profits, n, capacity);
            }
            break;
        }
    }
    break;
    case 5:
        optionIntegerLinearProgramming(pallets, weights, profits, n, capacity);
        break;
    case 6:
        // optionCompareAllAlgorithms(pallets, capacity);
        break;
    case 7:
        cout << "\nReturning to the main menu...\n";
        mainMenu();
        break;
    case 8:
        cout << "Exiting..." << endl;
        exit(0);
    default:
        break;
    }

    // Return to menu with the same data after algorithm execution
    if (option >= 1 && option <= 6)
    {
        cout << "\nReturning to menu with the same data...\n";
        this_thread::sleep_for(chrono::seconds(1));
        int next_option = optionsMenu();
        handleMenuOption(next_option, pallets, weights, profits, n, capacity);
    }
}

// Dataset selection and algorithm run
void datasetSelectionAndRun()
{
    // Dataset selection menu
    int datasetNumber;
    while (true)
    {
        cout << endl;
        cout << "=============================================" << endl;
        cout << "           DATASET SELECTION MENU" << endl;
        cout << "=============================================" << endl;
        cout << "Please select a dataset number (1-10):" << endl;
        cout << "  Datasets 1-4:  Standard datasets" << endl;
        cout << "  Datasets 5-10: Extra datasets" << endl;
        cout << "=============================================" << endl;
        cout << "Enter dataset number (1-10): ";
        cin >> datasetNumber;
        if (cin.fail() || datasetNumber < 1 || datasetNumber > 10)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number between 1 and 10." << endl;
        }
        else
        {
            break;
        }
    }
    // Build file paths
    string basePath = (datasetNumber >= 1 && datasetNumber <= 4) ? "datasets/" : "datasets-extra/";
    string formattedNumber = (datasetNumber < 10) ? ("0" + to_string(datasetNumber)) : to_string(datasetNumber);
    string truckFile = "../" + basePath + "TruckAndPallets_" + formattedNumber + ".csv";
    string palletFile = "../" + basePath + "Pallets_" + formattedNumber + ".csv";
    // Read truck and pallet data
    unsigned int trucksAndPallets[2];
    readTrucks(truckFile, trucksAndPallets);
    unsigned int capacity = trucksAndPallets[0];
    unsigned int n = trucksAndPallets[1];
    unsigned int *pallets = new unsigned int[n];
    unsigned int *weights = new unsigned int[n];
    unsigned int *profits = new unsigned int[n];
    readPallets(palletFile, pallets, weights, profits);

    // Show dataset info
    cout << endl
         << "Loaded dataset " << datasetNumber << ":\n";
    cout << "Truck capacity: " << capacity << endl;
    cout << "Number of pallets: " << n << endl;
    cout << setw(10) << "ID" << setw(10) << "Weight" << setw(10) << "Profit" << endl;
    for (unsigned int i = 0; i < n; i++)
    {
        cout << setw(10) << pallets[i] << setw(10) << weights[i] << setw(10) << profits[i] << endl;
    }
    // Proceed to algorithm selection
    int option = optionsMenu();
    handleMenuOption(option, pallets, weights, profits, n, capacity);
    delete[] pallets;
    delete[] weights;
    delete[] profits;
}

// should be vector<Pallet> pallets
void optionShowInfoMenu()
{
    cout << endl
         << "=============================================\n";
    cout << "       TRUCK PACKING - INPUT INFORMATION       \n";
    cout << "=============================================\n\n";

    cout << "Choose your input method:\n";
    cout << "1. Batch Mode (file input)\n";
    cout << "2. Interactive Mode (console input)\n";
    cout << "\nEnter your choice (1 or 2): ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        cout << "\nBATCH MODE INSTRUCTIONS:\n";
        cout << "1. Create a text file with the following format:\n";
        cout << "   First line: Truck capacity (integer)\n";
        cout << "   Subsequent lines: Pallet weight and value pairs\n";
        cout << "   Example:\n";
        cout << "   150\n";
        cout << "   23 45\n";
        cout << "   37 72\n";
        cout << "   42 60\n";
        cout << "2. Run the program with: ./truck_packer input.txt\n";

        cout << "\nReturning to main menu...\n";
        this_thread::sleep_for(chrono::seconds(3));

        // Create dummy arrays for going back to main menu
        unsigned int weights[1] = {0};
        unsigned int profits[1] = {0};
        unsigned int n = 0;

        mainMenu();
    }
    else if (choice == 2)
    {
        cout << "\nINTERACTIVE MODE INSTRUCTIONS:\n";
        cout << "1. You will be prompted to enter the truck's maximum weight capacity.\n";
        cout << "2. Next, enter the number of pallets you want to consider.\n";
        cout << "3. Then, specify the maximum number of pallets allowed (enter 0 for no limit).\n";
        cout << "4. For each pallet, enter its ID, weight, and profit in the format: palletID weight profit (with a space between)\n";
        cout << "   Example:\n";
        cout << "   1 23 45\n";
        cout << "   2 37 72\n";
        cout << "   3 42 60\n";
        cout << "5. After entering all pallets, you will see a summary of your input and can proceed to select and run algorithms.\n";
        cout << "\nReturning to main menu...\n";
        this_thread::sleep_for(chrono::seconds(3));
        unsigned int weights[1] = {0};
        unsigned int profits[1] = {0};
        unsigned int n = 0;
       
        mainMenu();
    }
    else
    {
        cout << "Invalid choice!\n";
        cout << "\nReturning to main menu...\n";
        this_thread::sleep_for(chrono::seconds(3));

        // Create dummy arrays for going back to main menu
        unsigned int weights[1] = {0};
        unsigned int profits[1] = {0};
        unsigned int n = 0;

        mainMenu();
    }
}

void optionExhaustiveSearch(unsigned int pallets[], unsigned int weights[],
                            unsigned int profits[], unsigned int n,
                            unsigned int capacity)
{
    std::cout << "\nRunning Exhaustive Search Algorithm...\n";
    std::cout << "Truck capacity: " << capacity << "\n";
    std::cout << "Number of available pallets: " << n << "\n\n";

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run the algorithm
    BFSol solution = knapsackBF(profits, weights, n, capacity);

    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Output the results
    OutputExhaustiveSolution(pallets, weights, profits, n, solution, duration.count() / 1000.0);
}

void optionDynamicProgramming(unsigned int pallets[], unsigned int weights[],
                              unsigned int profits[], unsigned int n,
                              unsigned int capacity)
{
    std::cout << "\nRunning Dynamic Programming Algorithm...\n";
    std::cout << "Truck capacity: " << capacity << "\n";
    std::cout << "Number of available pallets: " << n << "\n\n";

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Create an array to track which items are used
    bool *usedItems = new bool[n]();

    // Run the algorithm
    unsigned int totalProfit = knapsackDP(profits, weights, n, capacity, usedItems);

    // Calculate total weight and number of used pallets
    unsigned int totalWeight = 0;
    unsigned int palletCount = 0;

    for (unsigned int i = 0; i < n; i++)
    {
        if (usedItems[i])
        {
            totalWeight += weights[i];
            palletCount++;
        }
    }

    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Use the OutputDynamicProgramming function to display results
    OutputDynamicProgramming(pallets, weights, profits, n,
                             totalProfit, totalWeight, palletCount,
                             usedItems, duration.count() / 1000.0);

    // Clean up
    delete[] usedItems;
}

void optionBacktracking(unsigned int pallets[], unsigned int weights[],
                        unsigned int profits[], unsigned int n,
                        unsigned int capacity)
{
    std::cout << "\nRunning Backtracking Algorithm...\n";
    std::cout << "Truck capacity: " << capacity << "\n";
    std::cout << "Number of available pallets: " << n << "\n\n";

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run the algorithm
    BTSol solution = knapsackBT(profits, weights, n, capacity);

    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Use the OutputBacktracking function to display results
    OutputBacktracking(pallets, weights, profits, n, solution, duration.count() / 1000.0);
}

void optionGreedyRatio(unsigned int pallets[], unsigned int weights[],
                       unsigned int profits[], unsigned int n,
                       unsigned int capacity)
{
    std::cout << "\nRunning Greedy Algorithm (Weight-to-Profit Ratio)...\n";
    std::cout << "Truck capacity: " << capacity << "\n";
    std::cout << "Number of available pallets: " << n << "\n\n";

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run the algorithm
    GreedySol solution = knapsackGreedyRatio(profits, weights, n, capacity);

    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Output the results
    OutputGreedyApproximation(pallets, weights, profits, n, solution, duration.count() / 1000.0);
}

void optionGreedyProfit(unsigned int pallets[], unsigned int weights[],
                        unsigned int profits[], unsigned int n,
                        unsigned int capacity)
{
    std::cout << "\nRunning Greedy Algorithm (Biggest Profit Values)...\n";
    std::cout << "Truck capacity: " << capacity << "\n";
    std::cout << "Number of available pallets: " << n << "\n\n";

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run the algorithm
    GreedySol solution = knapsackGreedyProfit(profits, weights, n, capacity);

    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Output the results
    OutputGreedyApproximation(pallets, weights, profits, n, solution, duration.count() / 1000.0);
}

void optionGreedyMaximum(unsigned int pallets[], unsigned int weights[],
                         unsigned int profits[], unsigned int n,
                         unsigned int capacity)
{
    std::cout << "\nRunning Greedy Algorithm (Maximum of Both Approaches)...\n";
    std::cout << "Truck capacity: " << capacity << "\n";
    std::cout << "Number of available pallets: " << n << "\n\n";

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run the algorithm
    GreedySol solution = knapsackGreedyMaximum(profits, weights, n, capacity);

    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Output the results
    OutputGreedyApproximation(pallets, weights, profits, n, solution, duration.count() / 1000.0);
}

void optionIntegerLinearProgramming(unsigned int pallets[], unsigned int weights[],
                           unsigned int profits[], unsigned int n,
                           unsigned int capacity) {
    std::cout << "\nRunning Integer Linear Programming (PuLP)...\n";
    std::cout << "Truck capacity: " << capacity << "\n";
    std::cout << "Number of available pallets: " << n << "\n\n";

    // Create input.txt for Python script
    std::ofstream inputFile("input.txt");
    inputFile << n << "\n";
    inputFile << capacity << "\n";
    for (unsigned int i = 0; i < n; i++) inputFile << weights[i] << " ";
    inputFile << "\n";
    for (unsigned int i = 0; i < n; i++) inputFile << profits[i] << " ";
    inputFile.close();

    // Run Python script
    auto start = std::chrono::high_resolution_clock::now();
    int ret = system("python ../Approaches/knapsack_solver.py input.txt output.txt");
    if (ret != 0) {
        std::cerr << "Failed to run ILP solver.\n";
        return;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Parse output.txt
    std::ifstream outputFile("output.txt");
    int totalProfit = 0, totalWeight = 0;
    std::vector<int> selectedIndices;
    std::string line;

    if (outputFile.is_open()) {
        // Read total profit
        if (std::getline(outputFile, line)) {
            totalProfit = std::stoi(line);
        }

        // Read total weight
        if (std::getline(outputFile, line)) {
            totalWeight = std::stoi(line);
        }

        // Third line contains the selected pallet indices
        if (std::getline(outputFile, line)) {
            std::istringstream iss(line);
            int index;
            while (iss >> index) {
                // Add the index (it's 0-based in the output file)
                selectedIndices.push_back(index);
            }
        }
        outputFile.close();
    } else {
        std::cerr << "Unable to open output.txt file\n";
        return;
    }

    // Use the OutputLinearProgramming function to display results
    OutputIntegerLinearProgramming(pallets, weights, profits, n, capacity, 
                          totalProfit, totalWeight, selectedIndices,
                          duration.count() / 1000.0);
}

unsigned int *interactiveDataEntry()
{
    int inputCapacity, inputNumPallets; // Using signed int for initial input
    int inputPalletID, inputWeight, inputProfit;         // Using signed int for pallet data
    unsigned int capacity, numPallets;

    cout << "\n=============================================\n";
    cout << "            INTERACTIVE DATA ENTRY           \n";
    cout << "=============================================\n\n";

    // Get truck capacity with improved validation
    cout << "Enter truck capacity (maximum weight): ";
    while (!(cin >> inputCapacity) || inputCapacity <= 0)
    {
        cout << "Invalid input. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    capacity = static_cast<unsigned int>(inputCapacity); // Safe conversion after validation
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer after successful read

    // Get number of pallets to enter with improved validation
    cout << "Enter the number of pallets: ";
    while (!(cin >> inputNumPallets) || inputNumPallets <= 0)
    {
        cout << "Invalid input. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    numPallets = static_cast<unsigned int>(inputNumPallets); // Safe conversion after validation
    cin.ignore(numeric_limits<streamsize>::max(), '\n');     // Clear input buffer after successful read


    // Allocate memory for the result array
    // Format: [capacity, numPallets, maxPallets, pallets..., weights..., profits...]
    unsigned int *result = new unsigned int[2 + 3 * numPallets];
    result[0] = capacity;
    result[1] = numPallets;
    // result[2] = maxPallets;

    // Arrays to hold pallet IDs, weights, and profits
    unsigned int *pallets = &result[2];
    unsigned int *weights = &result[2 + numPallets];
    unsigned int *profits = &result[2 + 2 * numPallets];

    cout << "\nEnter pallet data in the format 'palletID weight profit':\n";

    for (unsigned int i = 0; i < numPallets; i++)
    {
        cout << "Pallet #" << (i + 1) << ": ";
        bool validInput = false;

        while (!validInput)
        {
            if (cin >> inputPalletID >> inputWeight >> inputProfit)
            {
                if (inputPalletID < 0)
                {
                    cout << "Invalid input. Pallet ID must be non-negative: ";
                }
                else if (inputWeight <= 0)
                {
                    cout << "Invalid input. Weight must be positive: ";
                }
                else if (inputProfit < 0)
                {
                    cout << "Invalid input. Profit must be non-negative: ";
                }
                else
                {
                    // All inputs valid
                    pallets[i] = static_cast<unsigned int>(inputPalletID);
                    weights[i] = static_cast<unsigned int>(inputWeight);
                    profits[i] = static_cast<unsigned int>(inputProfit);
                    validInput = true;
                }
            }
            else
            {
                cout << "Invalid input. Please use format 'palletID weight profit': ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer after successful read
    }

    cout << "\nData entry complete!\n";
    cout << "Summary:\n";
    cout << "- Truck capacity: " << capacity << "\n";
    cout << "- Number of pallets: " << numPallets << "\n";

    cout << "Pallet Data:\n";
    cout << setw(10) << "ID" << setw(10) << "Weight" << setw(10) << "Profit" << "\n";
    cout << "--------------------------------\n";

    for (unsigned int i = 0; i < numPallets; i++)
    {
        cout << setw(10) << pallets[i] << setw(10) << weights[i] << setw(10) << profits[i] << "\n";
    }
    cout << "--------------------------------\n";

    return result;
}

int approximationSubmenu()
{
    cout << endl
         << "=============================================\n";
    cout << "       APPROXIMATION ALGORITHM OPTIONS       \n";
    cout << "=============================================\n\n";

    int choice;
    do
    {
        cout << "1: Greedy A (Weight-to-Profit Ratio)" << endl;
        cout << "2: Greedy B (Biggest Profit Values)" << endl;
        cout << "3: Maximum of Both Approaches" << endl;
        cout << "4: Back to Main Menu" << endl;
        cout << "Option: ";
        cin >> choice;
        cout << endl;

        if (choice < 1 || choice > 4)
            cout << "Invalid input. Please choose 1-4." << endl;
    } while (choice < 1 || choice > 4);

    return choice;
}

void optionCompareAllAlgorithms(unsigned int pallets[], unsigned int weights[],
                               unsigned int profits[], unsigned int n,
                               unsigned int capacity)
{
    std::vector<std::string> algoNames;
    algoNames.push_back("Exhaustive Search");
    algoNames.push_back("Dynamic Programming");
    algoNames.push_back("Backtracking");
    algoNames.push_back("Greedy Ratio");
    algoNames.push_back("Greedy Profit");
    algoNames.push_back("Greedy Maximum");
    algoNames.push_back("Integer LP");

    std::vector<std::string> spaceComplexities;
    spaceComplexities.push_back("O(2^n)");      // Exhaustive Search
    spaceComplexities.push_back("O(nW)");       // Dynamic Programming
    spaceComplexities.push_back("O(2^n)");      // Backtracking
    spaceComplexities.push_back("O(n log n)");  // Greedy Ratio
    spaceComplexities.push_back("O(n log n)");  // Greedy Profit
    spaceComplexities.push_back("O(n log n)");  // Greedy Maximum
    spaceComplexities.push_back("Depends");     // Integer LP

    std::vector<double> runningTimes;

    // 1. Exhaustive Search
    auto start = std::chrono::high_resolution_clock::now();
    BFSol bfSol = knapsackBF(profits, weights, n, capacity);
    auto end = std::chrono::high_resolution_clock::now();
    runningTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

    // 2. Dynamic Programming
    start = std::chrono::high_resolution_clock::now();
    bool *usedItems = new bool[n]();
    unsigned int dpProfit = knapsackDP(profits, weights, n, capacity, usedItems);
    end = std::chrono::high_resolution_clock::now();
    runningTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());
    delete[] usedItems;

    // 3. Backtracking
    start = std::chrono::high_resolution_clock::now();
    BTSol btSol = knapsackBT(profits, weights, n, capacity);
    end = std::chrono::high_resolution_clock::now();
    runningTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

    // 4. Greedy Ratio
    start = std::chrono::high_resolution_clock::now();
    GreedySol grSol = knapsackGreedyRatio(profits, weights, n, capacity);
    end = std::chrono::high_resolution_clock::now();
    runningTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

    // 5. Greedy Profit
    start = std::chrono::high_resolution_clock::now();
    GreedySol gpSol = knapsackGreedyProfit(profits, weights, n, capacity);
    end = std::chrono::high_resolution_clock::now();
    runningTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

    // 6. Greedy Maximum
    start = std::chrono::high_resolution_clock::now();
    GreedySol gmSol = knapsackGreedyMaximum(profits, weights, n, capacity);
    end = std::chrono::high_resolution_clock::now();
    runningTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

    // 7. Integer Linear Programming (calls external Python script)
    start = std::chrono::high_resolution_clock::now();
    std::ofstream inputFile("input.txt");
    inputFile << n << "\n";
    inputFile << capacity << "\n";
    for (unsigned int i = 0; i < n; i++) inputFile << weights[i] << " ";
    inputFile << "\n";
    for (unsigned int i = 0; i < n; i++) inputFile << profits[i] << " ";
    inputFile.close();
    int ret = system("python ../Approaches/knapsack_solver.py input.txt output.txt");
    end = std::chrono::high_resolution_clock::now();
    runningTimes.push_back(std::chrono::duration<double, std::milli>(end - start).count());

    OutputCompareAllAlgorithms(algoNames, runningTimes, spaceComplexities);
}


