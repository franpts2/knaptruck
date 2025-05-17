#include "MenuTesting.h"
#include "../ReadData/read.h"
#include "../InputOutput/Output.h"
#include "../Approaches/Exhaustive.h"
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

int datasetSelectionMenu() {
    int choice;
    
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "          BRUTE FORCE ALGORITHM TESTING MENU" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Please select a dataset number (1-10):" << std::endl;
    std::cout << "  Datasets 1-4:  Standard datasets" << std::endl;
    std::cout << "  Datasets 5-10: Extra datasets" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Enter dataset number (1-10): ";
    
    // Input validation to ensure a number between 1-10 is entered
    do {
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > 10) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number between 1 and 10: ";
        } else {
            break;
        }
    } while (true);
    
    return choice;
}

std::string getDatasetPath(int datasetNumber, bool isPalletFile) {
    std::string basePath;
    std::string filePrefix = isPalletFile ? "Pallets_" : "TruckAndPallets_";
    std::string fileExtension = ".csv";
    
    // Using "../" to navigate up from the build directory to the project root
    std::string relativePrefix = "../";
    
    // Choose the correct directory based on dataset number
    if (datasetNumber >= 1 && datasetNumber <= 4) {
        basePath = "datasets/";
    } else if (datasetNumber >= 5 && datasetNumber <= 10) {
        basePath = "datasets-extra/";
    } else {
        return ""; // Invalid dataset number
    }
    
    // Format the dataset number with leading zero if necessary
    std::string formattedNumber = (datasetNumber < 10) ? "0" + std::to_string(datasetNumber) : std::to_string(datasetNumber);
    
    return relativePrefix + basePath + filePrefix + formattedNumber + fileExtension;
}

bool runBruteForceOnDataset(int datasetNumber) {
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
    for (unsigned int i = 0; i < n; i++) {
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
    for (unsigned int i = 0; i < n; i++) {
        if (solution.used_pallets[i]) {
            std::cout << std::setw(10) << pallets[i] << std::setw(10) << weights[i] << std::setw(10) << profits[i] << std::endl;
        }
    }
    
    return true;
}

int runTestingMenu() {
    bool continueRunning = true;
    char choice;
    
    while (continueRunning) {
        // Display menu and get dataset selection
        int datasetNumber = datasetSelectionMenu();
        
        // Run brute force on selected dataset
        bool success = runBruteForceOnDataset(datasetNumber);
        
        if (!success) {
            std::cout << "Error processing dataset " << datasetNumber << ". Please try again." << std::endl;
        }
        
        // Ask if the user wants to continue testing
        std::cout << "\nDo you want to test another dataset? (y/n): ";
        std::cin >> choice;
        
        if (choice != 'y' && choice != 'Y') {
            continueRunning = false;
        }
    }
    
    std::cout << "\nThank you for testing the Brute Force algorithm!" << std::endl;
    return 0;
}