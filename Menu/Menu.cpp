#include "Menu.h"
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int optionsMenu() {
    cout << endl << "Hello user!" << endl;
    cout << "Welcome to the Truck Packing Optimization Tool!" << endl << endl;
    cout << "This tool helps solve the knapsack problem for logistics optimization." << endl;
    cout << "If you have doubts about the input format, check the Info section." << endl;

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
        cout << "7: Exit" << endl;
        cout << "Option: ";
        cin >> i;
        cout << endl;

        if (i < 1 || i > 7) cout << "Invalid input. Please choose 1-7." << endl;
    } while (i < 1 || i > 7);

    return i;
}

void handleMenuOption(int option, vector<unsigned int>& pallets, int capacity) {
    switch (option) {
        case 1:
            //optionExhaustiveSearch(pallets, capacity);
            break;
        case 2:
            //optionDynamicProgramming(pallets, capacity);
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
            //optionShowInfoMenu(pallets, capacity);
            break;
        case 7:
            cout << "Exiting..." << endl;
            exit(0);
        default:
            break;
    }
}

//should be vector<Pallet> pallets
void optionShowInfoMenu(vector<unsigned int>& pallets, int capacity) {
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
    }
    else if (choice == 2) {
        cout << "\nINTERACTIVE MODE INSTRUCTIONS:\n";
        cout << "1. Enter truck capacity (max weight)\n";
        cout << "2. Enter number of pallets\n";
        cout << "3. For each pallet, enter:\n";
        cout << "   - Weight (kg)\n";
        cout << "   - Profit (value of the goods)\n";
        cout << "The system will then compute optimal packing.\n";
    }
    else {
        cout << "Invalid choice!\n";
    }

    cout << "\nReturning to main menu...\n";
    this_thread::sleep_for(chrono::seconds(3));

    int option = optionsMenu();
    handleMenuOption(option, pallets, capacity);
}