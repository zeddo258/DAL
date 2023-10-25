#include <iostream>
#include <sstream>
#include <string>
#include "Maze.hpp"

int main() {
    int command = 0;

    do {
        Maze aMaze;
        std::string fileName;
        Modes mode = oneG;

        std::cout << std::endl << "*** Path Finding ***";
        std::cout << std::endl << "0. Quit    ";
        std::cout << std::endl << "1. One goal    ";
        std::cout << std::endl << "2. More goals  ";
        std::cout << std::endl << "********************";
        std::cout << std::endl << "Input a command (0, 1, 2): ";
        std::cin >> command;

        if (command == 1 || command == 2) {
            if (command == 2) {
                mode = moreG;
            }

            int fileNumber;
            std::cout << std::endl << "Input a starting file number (e.g., 101, 102, 103, etc): ";
            std::cin >> fileNumber;

            while (true) {
                std::stringstream fileNameStream;
                fileNameStream << "input" << fileNumber << ".txt";
                std::string currentFileName = fileNameStream.str();

                if (aMaze.load(currentFileName, mode)) {
                    Maze vMaze(aMaze);
                    bool success = aMaze.findGoals(vMaze);
                    mode = oneG;
                    vMaze.show();

                    if (success) {
                        aMaze.show();
                    }
                    vMaze.clear();
                } 
                else {
                    std::cout << "File " << currentFileName << " not existed!!!" << std::endl;
                    break;
                }
                fileNumber++;
                // mistake here maybe 
            }
        } else if (!command) {
            break;
        } else {
            std::cout << std::endl << "Command does not exist!" << std::endl;
        }
    } while (true);

    return 0;
}