#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <string>
#include "../Approaches/Exhaustive.h"
#include "../Approaches/Greedy.h"
#include "../Approaches/Backtracking.h"

void OutputExhaustiveSolution(unsigned int pallets[], unsigned int weights[],
                              unsigned int profits[], unsigned int n,
                              const BFSol &solution, double executionTime);

void OutputDynamicProgramming(unsigned int pallets[], unsigned int weights[],
                              unsigned int profits[], unsigned int n,
                              unsigned int totalProfit, unsigned int totalWeight,
                              unsigned int palletCount, const bool usedItems[],
                              double executionTime);

void OutputBacktracking(unsigned int pallets[], unsigned int weights[],
                        unsigned int profits[], unsigned int n,
                        const BTSol &solution, double executionTime);

void OutputGreedyApproximation(unsigned int pallets[], unsigned int weights[],
                               unsigned int profits[], unsigned int n,
                               const GreedySol &solution, double executionTime);

void OutputIntegerLinearProgramming(unsigned int pallets[], unsigned int weights[],
                            unsigned int profits[], unsigned int n,
                            unsigned int capacity, int totalProfit, int totalWeight,
                            const std::vector<int>& selectedIndices, double executionTime);

void OutputCompareAllAlgorithms(const std::vector<std::string>& names, 
                                const std::vector<double>& times, 
                                const std::vector<std::string>& spaceComplexities, 
                                const std::vector<std::string>& accuracyAlgorithms,
                                const std::vector<unsigned int>& profits);

#endif // OUTPUT_H
