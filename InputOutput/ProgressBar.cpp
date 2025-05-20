/**
 * @file ProgressBar.cpp
 * @brief Progress bar implementation for long-running algorithms
 */

#include "ProgressBar.h"
#include <iostream>
#include <iomanip>
#include <thread>

ProgressBar::ProgressBar(unsigned long long total) : 
    total_iterations(total), 
    current_iteration(0),
    visible(false) {
    start_time = std::chrono::high_resolution_clock::now();
}

void ProgressBar::update(unsigned long long iteration) {
    current_iteration = iteration;
    
    // Calculate the progress percentage
    float progress = static_cast<float>(current_iteration) / total_iterations;
    int bar_position = static_cast<int>(progress * BAR_WIDTH);
    int percent = static_cast<int>(progress * 100);
    
    // Print the progress bar
    std::cout << "\r[";
    for (int i = 0; i < BAR_WIDTH; ++i) {
        if (i < bar_position) std::cout << "=";
        else std::cout << " ";
    }
    std::cout << "] " << std::setw(3) << percent << "%" << std::flush;
    
    visible = true;
}

void ProgressBar::complete() {
    if (visible) {
        // Update to 100%
        std::cout << "\r[";
        for (int i = 0; i < BAR_WIDTH; ++i) {
            std::cout << "=";
        }
        std::cout << "] 100%" << std::flush;
        
        // Wait for a second before clearing the progress bar
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Clear the progress bar
        std::cout << "\r" << std::string(BAR_WIDTH + 10, ' ') << "\r" << std::flush;
    }
}

bool ProgressBar::shouldShow(int timeThresholdMs) {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
    
    // Only show the progress bar if the operation has been running for more than the threshold
    return duration > timeThresholdMs;
}