#pragma once
#include <string>
#include <vector>
#include <random>
#include <limits>
#include <iostream>
#include <fstream>

// Forward declarations
class Player;
class Spell;

inline bool randomChance(int percent)
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(1, 100);
    return dist(gen) <= percent;
}

inline int clamp(int value, int min, int max)
{
    return std::max(min, std::min(value, max));
}

inline void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void savePlayer(const Player& hero);
void loadPlayer();
void checkLevelUp(Player& hero);
