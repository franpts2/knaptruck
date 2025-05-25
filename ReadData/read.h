/**
 * @file read.h
 * @brief Functions for reading pallet and truck data from CSV files
 */

#ifndef READ_H
#define READ_H

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <sstream>

/**
 * @brief Reads pallet data from a CSV file
 *
 * @param filename Path to the CSV file containing pallet data
 * @param pallets Array to store pallet IDs
 * @param weights Array to store pallet weights
 * @param profits Array to store pallet profit values
 *
 * @note The CSV file should have a header row and columns for pallet ID, weight, and profit,
 *       separated by commas. The function skips the header row.
 */
void readPallets(const std::string &filename, unsigned int pallets[], unsigned int weights[], unsigned int profits[]);

/**
 * @brief Reads truck capacity and pallet count data from a CSV file
 *
 * @param filename Path to the CSV file containing truck data
 * @param trucksAndPallets Array to store the truck capacity [0] and pallet count [1]
 *
 * @note The CSV file should have a header row and columns for truck capacity and number of pallets,
 *       separated by commas. The function skips the header row.
 */
void readTrucks(const std::string &filename, unsigned int *trucksAndPallets);

#endif // READ_H