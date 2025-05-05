#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include "DelverHelpers.h"
#include "GameStates.cpp"
#pragma comment(lib, "winmm.lib") // Link Windows Multimedia library
using namespace std;
#include "DelverClasses.h"


void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) // Callback function to handle the end of the first sound
{
    if (uMsg == WOM_DONE)
    {  
        PlaySoundA("Tide.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); // Play the second sound on a loop asynchronously
    }
}

int main() 
{
    PlaySoundA("Vermin.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    while (true) 
    {
        int choice;
        cout << "\n*** Game Menu ***\n";
        cout << "1. Start a New Game\n";
        cout << "2. Load Game\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) 
        {
        case 1:
            cout << "Starting a New Game...\n";
            initiatePlayer();
            break;
        case 2:
            loadPlayer();
            break;
        case 3:
            cout << "Exiting game. Goodbye!\n";
            return 0; // Ends the program
        default:
            cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }
}
