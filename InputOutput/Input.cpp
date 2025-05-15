/**
 * @file Input.cpp
 * @brief Input handling for pallet loading system
 */

#include "Input.h"
#include "read.h"  // Your existing read functions
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;


bool InputExhaustive(unsigned int pallets[], unsigned int weights[],
                         unsigned int profits[], unsigned int &n,
                         unsigned int &capacity, unsigned int &max_pallets) {
    cout << "\n===== INTERACTIVE INPUT MODE =====\n";

    // Get truck capacity
    cout << "Enter truck capacity (max weight): ";
    while (!(cin >> capacity)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }

    // Get max pallets
    cout << "Enter maximum number of pallets allowed: ";
    while (!(cin >> max_pallets) || max_pallets <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }

    // Get number of pallets
    cout << "Enter number of pallets: ";
    while (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }

    // Get pallet details
    cout << "\nEnter pallet details (ID Weight Profit):\n";
    for (unsigned int i = 0; i < n; i++) {
        unsigned int id, weight, profit;
        cout << "Pallet " << i+1 << ": ";

        while (!(cin >> id >> weight >> profit)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter three integers (ID Weight Profit): ";
        }

        pallets[i] = id;
        weights[i] = weight;
        profits[i] = profit;
    }

    return true;
}