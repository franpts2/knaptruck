/**
 * @file ProgressBar.h
 * @brief Progress bar implementation for long-running algorithms
 */

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <iostream>
#include <string>
#include <chrono>

class ProgressBar {
private:
    static const int BAR_WIDTH = 70;
    unsigned long long total_iterations;
    unsigned long long current_iteration;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    bool visible;
    
public:
    /**
     * @brief Constructs a new Progress Bar object
     * @param total The total number of iterations that the algorithm will perform
     */
    ProgressBar(unsigned long long total);
    
    /**
     * @brief Updates the progress bar with the current iteration
     * @param iteration The current iteration number
     */
    void update(unsigned long long iteration);
    
    /**
     * @brief Completes the progress bar and removes it from the screen after 1 second
     */
    void complete();
    
    /**
     * @brief Checks if the algorithm is taking a significant amount of time and the progress bar should be shown
     * @param timeThresholdMs The time threshold in milliseconds
     * @return true if progress bar should be shown, false otherwise
     */
    bool shouldShow(int timeThresholdMs = 500);
};

#endif // PROGRESSBAR_H