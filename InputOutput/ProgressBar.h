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
    bool escape_message_shown;
    bool hidden_mode;
    
public:
    /**
     * @brief Constructs a new Progress Bar object
     * @param total The total number of iterations that the algorithm will perform
     * @param hidden If true, no progress bar will be shown but escape key detection will still work
     */
    ProgressBar(unsigned long long total, bool hidden = false);
    
    /**
     * @brief Updates the progress bar with the current iteration
     * @param iteration The current iteration number
     * @return true if user wants to continue, false if escape was pressed
     */
    bool update(unsigned long long iteration);
    
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
    
    /**
     * @brief Checks if escape key has been pressed
     * @return true if escape key has been pressed, false otherwise
     */
    bool checkForEscapeKey();
    
    /**
     * @brief Shows an escape message after the progress bar has been running for a minute
     * @return true if the message was shown, false otherwise
     */
    bool showEscapeMessageIfNeeded();
    
    /**
     * @brief Shows a "large dataset" message for datasets that are too large for normal processing
     * @param message Custom message to show (optional)
     */
    void showLargeDatasetMessage(const std::string& message = "");
    
    /**
     * @brief Check if escape was pressed (for large datasets without progress bar)
     * @return true if escape was pressed, false otherwise
     */
    bool checkCancellation();
};

#endif // PROGRESSBAR_H