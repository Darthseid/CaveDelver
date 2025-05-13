#include "MainMenu.h"   // Include the corresponding header
#include "DelverClasses.h" // Include header for Player, Enemy, Tile classes
#include "DelverMap.h"
#include "DelverHelpers.h"
#include "GameStates.h" // Include header for initiatePlayer, loadPlayer declarations
#include <iostream>
#include <limits>   // For std::numeric_limits
#include <ios>      // For std::streamsize
#pragma once

Cave cave;
void mainMenuLoop()  // Definition of the main menu loop function
{
    while (true)
    {
        int choice;
        std::cout << "\n*** Game Menu ***\n";
        std::cout << "1. Start a New Game\n";
        std::cout << "2. Load Game\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice)) 
        {      // Input validation
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue; // Ask for input again
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) 
        {
        case 1:
            std::cout << "Starting a New Game...\n";
            initiatePlayer(); // Call the function to start a new game
            break;
        case 2:
            std::cout << "Loading Game...\n";
            loadPlayer(); // Call the function to load a game
            break;
        case 3:
            std::cout << "Exiting game. Goodbye!\n";
            return; // Exit the mainMenuLoop function
        default:
            std::cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }
}