#include <iostream>
#include <thread>
#include <windows.h>   // For PlaySoundA
#include <mmsystem.h>  // For PlaySoundA and multimedia functions
#include "MainMenu.h"
#pragma comment(lib, "winmm.lib") // Linker directive for the Windows Multimedia library


void playBackgroundMusic()
{
    PlaySoundA("Vermin.wav", NULL, SND_FILENAME | SND_SYNC); // Background music function (unchanged)
    PlaySoundA("Tide.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

int main() 
{
    std::thread musicThread(playBackgroundMusic);
    musicThread.detach();    // Start the background music in a separate thread
    mainMenuLoop(); // Call the function that contains the main menu loop
    return 0; // The program execution will only reach here when the user chooses "Exit" from main menu.
}