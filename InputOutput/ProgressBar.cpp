/**
 * @file ProgressBar.cpp
 * @brief Progress bar implementation for long-running algorithms
 */

#include "ProgressBar.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

ProgressBar::ProgressBar(unsigned long long total, bool hidden) : 
    total_iterations(total), 
    current_iteration(0),
    visible(false),
    escape_message_shown(false),
    hidden_mode(hidden) {
    start_time = std::chrono::high_resolution_clock::now();
}

bool ProgressBar::update(unsigned long long iteration) {
    current_iteration = iteration;
    
    // In hidden mode, just check for cancellation
    if (hidden_mode) {
        return !checkCancellation();
    }
    
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
    
    // Check if we should display the escape message
    showEscapeMessageIfNeeded();
    
    // Check if escape key was pressed
    if (checkForEscapeKey()) {
        // Indicate to stop the algorithm
        return false;
    }
    
    return true;
}

void ProgressBar::complete() {
    if (hidden_mode) {
        return;
    }
    
    if (visible) {
        // Update to 100%
        std::cout << "\r[";
        for (int i = 0; i < BAR_WIDTH; ++i) {
            std::cout << "=";
        }
        std::cout << "] 100%" << std::flush;
        
        // Wait for a second before clearing the progress bar
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Clear the progress bar and any escape message
        std::cout << "\r" << std::string(BAR_WIDTH + 10, ' ') << "\r" << std::flush;
        if (escape_message_shown) {
            std::cout << std::string(60, ' ') << "\r" << std::flush;
        }
    }
}

bool ProgressBar::shouldShow(int timeThresholdMs) {
    if (hidden_mode) {
        return false;
    }
    
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
    
    // Only show the progress bar if the operation has been running for more than the threshold
    return duration > timeThresholdMs;
}

bool ProgressBar::checkForEscapeKey() {
    // Setup for non-blocking key check
    struct termios oldt, newt;
    int oldf;
    
    // Save terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    // Check for the escape key (ASCII 27)
    int ch = getchar();
    bool escapePressed = (ch == 27);
    
    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    return escapePressed;
}

bool ProgressBar::showEscapeMessageIfNeeded() {
    // Only show the message once
    if (escape_message_shown) {
        return true;
    }
    
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
    
    // Show message after a minute (60 seconds)
    if (duration > 60) {
        if (!hidden_mode) {
            std::cout << "\n\nThis sure is taking a lot of time... If you want to give up just press Esc!" << std::endl;
        }
        escape_message_shown = true;
        return true;
    }
    
    return false;
}

void ProgressBar::showLargeDatasetMessage(const std::string& message) {
    std::cout << "\nThis will take a while (not even the progress bar wanted to be here)." << std::endl;
    if (!message.empty()) {
        std::cout << message << std::endl;
    }
    std::cout << "Go grab a coffee or something! ☕ or just press Esc to stop the running algorithm" << std::endl;
}

bool ProgressBar::checkCancellation() {
    // Check if enough time has passed to start monitoring for escape key
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
    
    // Show escape message after a minute if not already shown
    if (duration > 60 && !escape_message_shown) {
        if (hidden_mode) {
            showEscapeMessageIfNeeded();
        }
    }
    
    // Only check for escape key after a minute to reduce overhead
    if (duration > 60 && checkForEscapeKey()) {
        return true;
    }
    
    return false;
}