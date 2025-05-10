#include <iostream>
#include <string>
#include <algorithm> // Add this include at the top of the file for std::clamp
#include <limits>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Spells.h"
#include "DelverClasses.h"
#include "DelverMap.h"
#pragma once
#undef min
#undef max

extern Map maps[5]; // 5 maps
extern int currentMapIndex;

bool randomChance(int percent)
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(1, 100);
    return dist(gen) <= percent;
}

int clamp(int value, int min, int max)
{
	return std::max(min, std::min(value, max)); // Clamp value between min and max
}

void clearInput()  // Helper: Clear input stream
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void savePlayer(const Player& hero) 
{
    std::ofstream out("Player.txt");
    if (!out.is_open()) 
    {
        std::cerr << "Error: Could not write Player.txt\n"; // Save Player to "Player.txt"
        return;
    }

    out << hero.maxHealth << ' ' << hero.currentHealth << '\n';
    out << hero.maxMana << ' ' << hero.currentMana << '\n';
    out << hero.accuracy << ' ' << hero.evasion << ' ' << hero.initiative << ' ' << hero.damage << '\n';
    out << hero.coordinates[0] << ' ' << hero.coordinates[1] << ' ' << hero.coordinates[2] << '\n';
    out << hero.spells.size() << '\n';
    for (const auto& spell : hero.spells) 
    {
        out << spell.name << '\n'
            << spell.manaCost << '\n'
            << spell.description << '\n';
    }
    maps[hero.coordinates[2]].saveMap();
    out.close();
    std::cout << "Player saved successfully.\n";
}

Player loadPlayer() 
{
    std::ifstream in("Player.txt");
    if (!in.is_open()) 
    {
        std::cerr << "Error: Could not open Player.txt\n"; // Load Player from "Player.txt"
        exit(1);
    }

    std::string name;
    std::getline(in, name);

    int maxHealth, currentHealth;
    in >> maxHealth >> currentHealth;

    int maxMana, currentMana;
    in >> maxMana >> currentMana;

    int accuracy, evasion, initiative, damage;
    in >> accuracy >> evasion >> initiative >> damage;

    int x, y, z;
    in >> x >> y >> z;

    int spellCount;
    in >> spellCount;
    in.ignore(); // consume newline

    std::vector<Spell> spells;
    for (int i = 0; i < spellCount; ++i) 
    {
        std::string spellName, description;
        int manaCost;

        std::getline(in, spellName);
        in >> manaCost;
        in.ignore(); // consume newline
        std::getline(in, description);

        spells.emplace_back(spellName, manaCost, description);
    }

    Player player(maxHealth, maxMana, accuracy, evasion, initiative, damage, x, y);
    player.currentHealth = currentHealth;
    player.currentMana = currentMana;
    player.coordinates[2] = z;
    player.spells = spells;

    maps[currentMapIndex].loadMap();
    std::cout << "Player loaded: " <<  "\n";
    return player;
}

void checkLevelUp(Player& hero) 
{
    int threshold = (hero.level * hero.level) / 2;

    if (hero.experience >= threshold) 
    {
        std::cout << "\n*** Level Up! ***\n";
        hero.level++;
        hero.currentHealth = hero.maxHealth;
        hero.currentMana = hero.maxMana;
        std::cout << "You are now level " << hero.level << "! HP and Mana fully restored.\n";

        std::cout << "Choose a stat to upgrade:\n";
        std::cout << "1. Max Health (+2)\n";
        std::cout << "2. Max Mana (+2)\n";
        std::cout << "3. Accuracy (+3)\n";
        std::cout << "4. Evasion (+3)\n";
        std::cout << "Your choice: ";

        int choice;
        std::cin >> choice;
        clearInput();

        switch (choice) 
        {
            case 1:
                hero.maxHealth += 2;
                std::cout << "Max Health increased to " << hero.maxHealth << "\n";
                break;
            case 2:
                hero.maxMana += 2;
                std::cout << "Max Mana increased to " << hero.maxMana << "\n";
                break;
            case 3:
                hero.accuracy += 3;
                std::cout << "Accuracy increased to " << hero.accuracy << "\n";
                break;
            case 4:
                hero.evasion += 3;
                std::cout << "Evasion increased to " << hero.evasion << "\n";
                break;
            default:
                std::cout << "Invalid choice. No stat upgraded.\n";
                break;
        }
        checkLevelUp(hero); // Recursive re-check if XP still qualifies for another level
    }
}
