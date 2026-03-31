#ifndef UI_H
#define UI_H

namespace ui {
    void printHeader();
    void printMenu();
    void printHelp();
    void printMode(bool verbose);
    void printRunning(int expNum);
    void printDone(int expNum);
    void printError(const char* message);
    void printExit();
    void waitForEnter();
    bool getUserInput(int& choice);
}

#endif