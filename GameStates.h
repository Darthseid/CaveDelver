#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <thread>
#include <chrono>
#include "MainMenu.h"
#include "DelverClasses.h"
#include "DelverMap.h"
#include "DelverTemplates.h"
#include "DelverHelpers.h"
#pragma once

    void playerAttack(Enemy& foe, Player& hero);
    void clearTile(Tile& tile);
    void enemyAttack(Enemy& foe, Player& hero);
    Enemy getEnemyForTile(int location[3]);
    void checkGameOver(Player& hero);
    bool checkDeadEnemy(Player& hero, Enemy& foe);
    bool playerGoesFirst(int playerInit, int enemyInit);
    void overWorld(Player& hero);
    void spellMenu(Player& hero, Enemy& foe);
    void playerCombatTurn(Player& hero, Enemy& foe);
    void handleCombat(Player& hero, Enemy& foe);
    void initiatePlayer();
    void checkGameCompletion();
    void handlePostMovementEvent(Player& hero);
    void movePlayer(Player& hero);
