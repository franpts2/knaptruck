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
    
    if (hidden_mode) {
        return !checkCancellation();
    }
    
    // calculate the progress percentage
    float progress = static_cast<float>(current_iteration) / total_iterations;
    int bar_position = static_cast<int>(progress * BAR_WIDTH);
    int percent = static_cast<int>(progress * 100);
    
    std::cout << "\r[";
    for (int i = 0; i < BAR_WIDTH; ++i) {
        if (i < bar_position) std::cout << "=";
        else std::cout << " ";
    }
    std::cout << "] " << std::setw(3) << percent << "%" << std::flush;
    
    visible = true;
    
    showEscapeMessageIfNeeded();
    
    if (checkForEscapeKey()) {
        return false;
    }
    
    return true;
}

void ProgressBar::complete() {
    if (hidden_mode) {
        return;
    }
    
    if (visible) {
        // update to 100%
        std::cout << "\r[";
        for (int i = 0; i < BAR_WIDTH; ++i) {
            std::cout << "=";
        }
        std::cout << "] 100%" << std::flush;
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // clear the progress bar and any escape message
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
    
    // only show the progress bar if the operation has been running for more than the threshold
    return duration > timeThresholdMs;
}

bool ProgressBar::checkForEscapeKey() {
    struct termios oldt, newt;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    // check for the esc key
    int ch = getchar();
    bool escapePressed = (ch == 27);
    
    // restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    return escapePressed;
}

bool ProgressBar::showEscapeMessageIfNeeded() {
    if (escape_message_shown) {
        return true;
    }
    
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
    
    // show message after a minute
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
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
    
    if (duration > 60 && !escape_message_shown) {
        if (hidden_mode) {
            showEscapeMessageIfNeeded();
        }
    }
    
    if (duration > 60 && checkForEscapeKey()) {
        return true;
    }
    
    return false;
}