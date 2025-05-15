/**
* @file Input.h
 * @brief Input handling for pallet loading system
 */

#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>


/**
 * @brief Interactive input for pallet loading problem
 * @param pallets Array to store pallet IDs
 * @param weights Array to store pallet weights
 * @param profits Array to store pallet profits
 * @param n Number of pallets (output)
 * @param capacity Truck capacity (output)
 * @param max_pallets Maximum pallets allowed (output)
 * @return true if input succeeded, false otherwise
 */
bool InputExhaustive(unsigned int pallets[], unsigned int weights[],
                         unsigned int profits[], unsigned int &n,
                         unsigned int &capacity, unsigned int &max_pallets);

#endif // INPUT_H