#include "Menu.h"
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip> // For std::setw
#include <limits>  // For std::numeric_limits

using namespace std;

int optionsMenu() {
    cout << endl << "Loading options..." << endl;
    cout.flush();
    this_thread::sleep_for(chrono::seconds(1));

    cout << "----------------------------------------------" << endl;
    cout << "          TRUCK PACKING OPTIMIZATION" << endl;
    cout << "----------------------------------------------" << endl << endl;

    int i;
    do {
        cout << "1: Exhaustive Search Algorithm" << endl;
        cout << "2: Dynamic Programming Approach" << endl;
        cout << "3: Approximation Algorithm" << endl;
        cout << "4: Linear Integer Programming" << endl;
        cout << "5: Compare All Algorithms" << endl;
        cout << "6: Info & Instructions" << endl;
        cout << "7: Change Input Data" << endl;
        cout << "8: Exit" << endl;
        cout << "Option: ";
        cin >> i;
        cout << endl;

        if (i < 1 || i > 8) cout << "Invalid input. Please choose 1-8." << endl;
    } while (i < 1 || i > 8);

    return i;
}

void handleMenuOption(int option, unsigned int pallets[], unsigned int weights[],
                     unsigned int profits[], unsigned int n,
                     int capacity, unsigned int max_pallets) {
    switch (option) {
        case 1:
            optionExhaustiveSearch(pallets, weights, profits, n, capacity, max_pallets);
            break;
        case 2:
            optionDynamicProgramming(pallets, weights, profits, n, capacity, max_pallets);
            break;
        case 3:
            //optionApproximation(pallets, capacity);
            break;
        case 4:
            //optionLinearProgramming(pallets, capacity);
            break;
        case 5:
            //optionCompareAllAlgorithms(pallets, capacity);
            break;
        case 6:
            optionShowInfoMenu(pallets, capacity);
            break;
        case 7:
            // Change Input Data option
            {
                unsigned int* data = interactiveDataEntry();
                
                // Extract data and call menu again with new data
                unsigned int new_capacity = data[0];
                unsigned int new_n = data[1];
                unsigned int new_max_pallets = data[2];
                
                // Extract arrays
                unsigned int* new_pallets = &data[3];
                unsigned int* new_weights = &data[3 + new_n];
                unsigned int* new_profits = &data[3 + 2 * new_n];
                
                int next_option = optionsMenu();
                handleMenuOption(next_option, new_pallets, new_weights, new_profits, new_n, new_capacity, new_max_pallets);
                
                // Clean up allocated memory
                delete[] data;
            }
            break;
        case 8:
            cout << "Exiting..." << endl;
            exit(0);
        default:
            break;
    }
    
    // Return to menu with the same data after algorithm execution
    if (option >= 1 && option <= 5) {
        cout << "\nReturning to menu with the same data...\n";
        this_thread::sleep_for(chrono::seconds(1));
        int next_option = optionsMenu();
        handleMenuOption(next_option, pallets, weights, profits, n, capacity, max_pallets);
    }
}

//should be vector<Pallet> pallets
void optionShowInfoMenu(unsigned int pallets[], int capacity) {
    cout << endl << "=============================================\n";
    cout << "       TRUCK PACKING - INPUT INFORMATION       \n";
    cout << "=============================================\n\n";

    cout << "Choose your input method:\n";
    cout << "1. Batch Mode (file input)\n";
    cout << "2. Interactive Mode (console input)\n";
    cout << "\nEnter your choice (1 or 2): ";

    int choice;
    cin >> choice;

    if (choice == 1) {
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
        unsigned int max_pallets = 0;
        
        int option = optionsMenu();
        handleMenuOption(option, pallets, weights, profits, n, capacity, max_pallets);
    }
    else if (choice == 2) {
        // Run interactive data entry
        unsigned int* data = interactiveDataEntry();
        
        // Extract data from the result array
        unsigned int new_capacity = data[0];
        unsigned int n = data[1];
        unsigned int max_pallets = data[2];
        
        // Extract arrays
        unsigned int* new_pallets = &data[3];
        unsigned int* weights = &data[3 + n];
        unsigned int* profits = &data[3 + 2 * n];
        
        // Forward directly to options menu
        int option = optionsMenu();
        handleMenuOption(option, new_pallets, weights, profits, n, new_capacity, max_pallets);
        
        // Clean up allocated memory
        delete[] data;
    }
    else {
        cout << "Invalid choice!\n";
        cout << "\nReturning to main menu...\n";
        this_thread::sleep_for(chrono::seconds(3));
        
        // Create dummy arrays for going back to main menu
        unsigned int weights[1] = {0};
        unsigned int profits[1] = {0};
        unsigned int n = 0;
        unsigned int max_pallets = 0;
        
        int option = optionsMenu();
        handleMenuOption(option, pallets, weights, profits, n, capacity, max_pallets);
    }
}

void optionExhaustiveSearch(unsigned int pallets[], unsigned int weights[],
                           unsigned int profits[], unsigned int n,
                           unsigned int capacity, unsigned int max_pallets) {
    std::cout << "\nRunning Exhaustive Search Algorithm...\n";
    std::cout << "Truck capacity: " << capacity << "\n";
    std::cout << "Max pallets allowed: " << max_pallets << "\n";
    std::cout << "Number of available pallets: " << n << "\n\n";

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run the algorithm
    BFSol solution = knapsackBF(profits, weights, n, capacity, max_pallets);

    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Algorithm execution time: " << duration.count() << "ms\n";

    // Output the results
    OutputExhaustiveSolution(pallets, weights, profits, n, solution);
}

void optionDynamicProgramming(unsigned int pallets[], unsigned int weights[],
                             unsigned int profits[], unsigned int n,
                             unsigned int capacity, unsigned int max_pallets) {
    std::cout << "\nRunning Dynamic Programming Algorithm...\n";
    std::cout << "Truck capacity: " << capacity << "\n";
    std::cout << "Number of available pallets: " << n << "\n\n";

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();
    
    // Create an array to track which items are used
    bool* usedItems = new bool[n]();
    
    // Run the algorithm
    unsigned int totalProfit = knapsackDP(profits, weights, n, capacity, usedItems);
    
    // Calculate total weight and number of used pallets
    unsigned int totalWeight = 0;
    unsigned int palletCount = 0;
    
    for (unsigned int i = 0; i < n; i++) {
        if (usedItems[i]) {
            totalWeight += weights[i];
            palletCount++;
        }
    }
    
    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Use the OutputDynamicProgramming function to display results
    OutputDynamicProgramming(pallets, weights, profits, n, 
                             totalProfit, totalWeight, palletCount, 
                             usedItems, duration.count());
    
    // Clean up
    delete[] usedItems;
}

unsigned int* interactiveDataEntry() {
    int inputCapacity, inputNumPallets, inputMaxPallets; // Using signed int for initial input
    int inputPalletID, inputWeight, inputProfit; // Using signed int for pallet data
    unsigned int capacity, numPallets, maxPallets;
    
    cout << "\n=============================================\n";
    cout << "            INTERACTIVE DATA ENTRY           \n";
    cout << "=============================================\n\n";
    
    // Get truck capacity with improved validation
    cout << "Enter truck capacity (maximum weight): ";
    while(!(cin >> inputCapacity) || inputCapacity <= 0) {
        cout << "Invalid input. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    capacity = static_cast<unsigned int>(inputCapacity); // Safe conversion after validation
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer after successful read
    
    // Get number of pallets to enter with improved validation
    cout << "Enter the number of pallets: ";
    while(!(cin >> inputNumPallets) || inputNumPallets <= 0) {
        cout << "Invalid input. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    numPallets = static_cast<unsigned int>(inputNumPallets); // Safe conversion after validation
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer after successful read
    
    // Get max pallets allowed with improved validation
    cout << "Enter maximum number of pallets allowed (or 0 for no limit): ";
    while(!(cin >> inputMaxPallets) || inputMaxPallets < 0) {
        cout << "Invalid input. Please enter a non-negative number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    maxPallets = static_cast<unsigned int>(inputMaxPallets); // Safe conversion after validation
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer after successful read
    
    if (maxPallets == 0 || maxPallets > numPallets) {
        maxPallets = numPallets;  // No limit or limit exceeds available pallets
    }
    
    // Allocate memory for the result array
    // Format: [capacity, numPallets, maxPallets, pallets..., weights..., profits...]
    unsigned int* result = new unsigned int[3 + 3 * numPallets];
    result[0] = capacity;
    result[1] = numPallets;
    result[2] = maxPallets;
    
    // Arrays to hold pallet IDs, weights, and profits
    unsigned int* pallets = &result[3];
    unsigned int* weights = &result[3 + numPallets];
    unsigned int* profits = &result[3 + 2 * numPallets];
    
    cout << "\nEnter pallet data in the format 'palletID weight profit':\n";
    
    for (unsigned int i = 0; i < numPallets; i++) {
        cout << "Pallet #" << (i+1) << ": ";
        bool validInput = false;
        
        while (!validInput) {
            if (cin >> inputPalletID >> inputWeight >> inputProfit) {
                if (inputPalletID < 0) {
                    cout << "Invalid input. Pallet ID must be non-negative: ";
                } else if (inputWeight <= 0) {
                    cout << "Invalid input. Weight must be positive: ";
                } else if (inputProfit < 0) {
                    cout << "Invalid input. Profit must be non-negative: ";
                } else {
                    // All inputs valid
                    pallets[i] = static_cast<unsigned int>(inputPalletID);
                    weights[i] = static_cast<unsigned int>(inputWeight);
                    profits[i] = static_cast<unsigned int>(inputProfit);
                    validInput = true;
                }
            } else {
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
    cout << "- Max pallets allowed: " << maxPallets << "\n\n";
    
    cout << "Pallet Data:\n";
    cout << setw(10) << "ID" << setw(10) << "Weight" << setw(10) << "Profit" << "\n";
    cout << "--------------------------------\n";
    
    for (unsigned int i = 0; i < numPallets; i++) {
        cout << setw(10) << pallets[i] << setw(10) << weights[i] << setw(10) << profits[i] << "\n";
    }
    cout << "--------------------------------\n";
    
    return result;
}
