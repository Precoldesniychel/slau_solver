#include "ui.h"
#include <iostream>
#include <string>
#include <limits>

void ui::printHeader() {
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << "       SLAU Solver Comparison - Interactive Mode        \n";
    std::cout << "========================================================\n";
    std::cout << "  Methods: Gauss (no pivot), Gauss (partial pivot), LU  \n";
    std::cout << "========================================================\n";
}

void ui::printMenu() {
    std::cout << "\n";
    std::cout << "================== MAIN MENU ==================\n";
    std::cout << "  1. Run Experiment 4.1 (Single System Time)\n";
    std::cout << "  2. Run Experiment 4.2 (Multiple Right-Hand Sides)\n";
    std::cout << "  3. Run Experiment 4.3 (Hilbert Matrix Accuracy)\n";
    std::cout << "  4. Run Experiment 4.4 (Pre-computed Base)\n";
    std::cout << "  5. Run All Experiments\n";
    std::cout << "  6. Switch Mode\n";
    std::cout << "  7. Show Help\n";
    std::cout << "  0. Exit\n";
    std::cout << "===============================================\n";
    std::cout << "> Enter choice: ";
    std::cout.flush();
}

void ui::printHelp() {
    std::cout << "\n";
    std::cout << "================== HELP ==================\n";
    std::cout << "This program compares SLAU solving methods:\n";
    std::cout << "  - Gauss elimination (without pivoting)\n";
    std::cout << "  - Gauss elimination (with partial pivoting)\n";
    std::cout << "  - LU decomposition\n\n";
    std::cout << "Experiments:\n";
    std::cout << "  4.1: Compare solution time for different matrix sizes\n";
    std::cout << "  4.2: Show LU advantage with multiple right-hand sides\n";
    std::cout << "  4.3: Test accuracy on ill-conditioned Hilbert matrices\n";
    std::cout << "  4.4: Pre-computed LU base vs new RHS\n\n";
    std::cout << "Verbose Mode: Shows sample matrices and vectors\n";
    std::cout << "============================================\n";
}

void ui::printMode(bool verbose) {
    std::cout << "\n[INFO] Current mode: " 
              << (verbose ? "Verbose (matrices shown)" : "Quick (tables only)") 
              << std::endl;
}

void ui::printRunning(int expNum) {
    if (expNum == 0) {
        std::cout << "[RUN] Starting All Experiments..." << std::endl;
    } else {
        std::cout << "[RUN] Starting Experiment 4." << expNum << "..." << std::endl;
    }
}

void ui::printDone(int expNum) {
    if (expNum == 0) {
        std::cout << "[DONE] All experiments completed." << std::endl;
    } else {
        std::cout << "[DONE] Experiment 4." << expNum << " completed." << std::endl;
    }
}

void ui::printError(const char* message) {
    std::cout << "\n[ERROR] " << message << std::endl;
}

void ui::printExit() {
    std::cout << "\n[EXIT] Exiting program. Goodbye!" << std::endl;
}

void ui::waitForEnter() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "\nPress Enter to continue...";
    std::cout.flush();
    
    std::cin.get();
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool ui::getUserInput(int& choice) {
    std::string input;
    std::getline(std::cin, input);
    
    if (input.empty()) {
        return false;
    }
    
    try {
        choice = std::stoi(input);
        return true;
    } catch (...) {
        return false;
    }
}