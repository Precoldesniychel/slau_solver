#include <iostream>
#include "ui.h"
#include "experiments.h"

int main() {
    bool verbose = false;
    bool running = true;

    ui::printHeader();
    ui::printMode(verbose);

    while (running) {
        ui::printMenu();
        
        int choice;
        if (!ui::getUserInput(choice)) {
            ui::printError("Empty input! Please enter a number (0-7).");
            continue;
        }
        
        std::cout << "\n";

        switch (choice) {
            case 1:
                ui::printRunning(1);
                experiments::runExperiment4_1(verbose);
                ui::printDone(1);
                ui::waitForEnter();
                break;
                
            case 2:
                ui::printRunning(2);
                experiments::runExperiment4_2(verbose);
                ui::printDone(2);
                ui::waitForEnter();
                break;
                
            case 3:
                ui::printRunning(3);
                experiments::runExperiment4_3(verbose);
                ui::printDone(3);
                ui::waitForEnter();
                break;
                
            case 4:
                ui::printRunning(4);
                experiments::runExperiment4_4(verbose);
                ui::printDone(4);
                ui::waitForEnter();
                break;
                
            case 5:
                ui::printRunning(0);
                experiments::runExperiment4_1(verbose);
                experiments::runExperiment4_2(verbose);
                experiments::runExperiment4_3(verbose);
                experiments::runExperiment4_4(verbose);
                ui::printDone(0);
                ui::waitForEnter();
                break;
                
            case 6:
                verbose = !verbose;
                ui::printMode(verbose);
                break;
                
            case 7:
                ui::printHelp();
                break;
                
            case 0:
                ui::printExit();
                running = false;
                break;
                
            default:
                ui::printError("Invalid choice! Please enter a number (0-7).");
                break;
        }
    }

    std::cout << "\n============================================\n";
    std::cout << "  Program terminated successfully.\n";
    std::cout << "============================================\n";
    return 0;
}