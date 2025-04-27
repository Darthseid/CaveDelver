#include <iostream>
#include <string>
#include <limits>
#include "DelverClasses.h"
#include "DelverMap.h"
#include <fstream>
#include "DelverHelpers.h"
#include "DelverTemplates.h"
#include "Spells.cpp"
#include <thread>
#include <chrono>

void movePlayer()
{
    while (true)
    {
        std::cout << "\nChoose direction (N/S/E/W): ";
        char dir;
        std::cin >> dir;
        clearInput();
        int newX = player.coordinates[0];
        int newY = player.coordinates[1];
        switch (toupper(dir)) 
        {
        case 'N': newY += 1; break;
        case 'S': newY -= 1; break;
        case 'E': newX += 1; break;
        case 'W': newX -= 1; break;
        default:
            std::cout << "Invalid input. Try N/S/E/W.\n";
            continue;
        }
        if (newX < 0 || newX >= MAP_SIZE || newY < 0 || newY >= MAP_SIZE) {
            std::cout << "You cannot move off the map.\n";
            continue;
        }
        Player.coordinates[0] = newX;
        Player.coordinates[1] = newY;
        break;
    }
    handlePostMovementEvent();
}

Enemy getEnemyForTile() 
{
    std::string type = maps[currentMapIndex]
        .grid[player.coordinates[0]][player.coordinates[1]].type;

        if (type == "Enemy") 
        {
            if (currentMapIndex == 0) return goblin;
            if (currentMapIndex == 1) return orc;
            if (currentMapIndex == 2) return ogre;
            if (currentMapIndex == 3) return troll;
            if (currentMapIndex == 4) return goliath;
        }
        else if (type == "Boss")
        {
            if (currentMapIndex == 0) return hugeBear;
            if (currentMapIndex == 1) return golem;
            if (currentMapIndex == 2) return spider;
            if (currentMapIndex == 3) return wyvern;
            if (currentMapIndex == 4) return hydra;
        }

        std::cerr << "No valid enemy found for combat.\n";
        return goblin; // default fallback
}

bool playerGoesFirst(int playerInit, int enemyInit)
{
    if (playerInit > enemyInit) return true;
    if (enemyInit > playerInit) return false;
    return RandomChance(50); // initiative tie
}

void playerCombatTurn(Player& hero, Enemy& foe) 
{
    std::cout << "\nChoose Action: [A]ttack, [M]agic, [F]lee: ";
    char choice;
    std::cin >> choice;
    clearInput();
    switch (toupper(choice)) 
    {
    case 'A':
        playerAttack(foe, hero);
        break;
    case 'M':
        spellMenu(hero, foe);
        break;
    case 'F':
        if (RandomChance(50)) 
        {
            std::cout << "You successfully fled.\n";
            overWorld();
            break;
        }
        else 
        {
            std::cout << "Flee failed! The enemy attacks!\n";
            enemyAttack(foe, hero);
            break;
        }
    default:
        std::cout << "Invalid choice. Try again.\n";
        playerCombatTurn(); // re-prompt
    }
}

void playerAttack(Enemy& foe, Player& hero) 
{
    int chance = player.accuracy - foe.evasion();
    if (RandomChance(chance)) 
    {
        std::cout << "\n You Hit!";
        foe.health -= hero.damage;
        std::cout << "\n" << foe.name << " takes " << hero.damage << " damage (HP left: " << foe.health << ")";
    }
    else 
        std::cout << "You Missed!\n";
}

void clearTile(int location[2])
{
        Tile& tile = maps[currentMapIndex].grid[player.coordinates[0]][player.coordinates[1]]; //Player's current location.
        tile.cleared = true;  // Mark the tile as cleared
}

void enemyAttack(Enemy& foe, Player& hero)
{
    int chance = player.accuracy - enemy.evasion();
    if (RandomChance(chance))
    {
        std::cout << "\n You got Hit!";
        hero.currentHealth -= foe.damage;
        std::cout << "\n You take " << foe.damage << " damage (HP left: " << player.currentHealth << ")";
    }
    else
        std::cout << foe.name << "\n Missed!";
}

bool spellMenu(Player& hero, Enemy& foe) 
{
    std::cout << "\n=== Spellbook ===\n";
    for (size_t i = 0; i < hero.spells.size(); ++i)
    {
        const Spell& s = hero.spells[i];
        std::cout << i + 1 << ". " << s.name << " (Cost: " << s.manaCost << ") - " << s.description << "\n";
    }
    std::cout << "0. Cancel\n";
    std::cout << "Select a spell: ";

    int choice;
    std::cin >> choice;
    clearInput();

    if (choice == 0) return false; // cancel -> return to combat menu

    if (choice < 1 || choice > static_cast<int>(player.spells.size())) 
    {
        std::cout << "Invalid selection.\n";
        return SpellMenu(foe); // re-prompt
    }

    Spell& selected = hero.spells[choice - 1];
    if (hero.currentMana < selected.manaCost) 
    {
        std::cout << "Not enough mana to cast " << selected.name << ".\n";
        return false;
    }

    // Spend mana
    player.currentMana -= selected.manaCost;
    std::cout << "You cast " << selected.name << "!\n";

    // TODO: Implement spell effect by name (in next step)
    // For now, just placeholder
    std::cout << "The spell effect takes place.\n";

    return true; // spell was cast successfully
}

void handleCombat(Player& hero, Enemy& foe) 
{
    int currentRound = 0;
    bool playerAttacksFirst = playerGoesFirst(hero.initiative, foe, initiative);
    while (hero.currentHealth > 0 && foe.getHealth() > 0)
    {
        std::cout << "Round " << currentRound + 1 << "\n";
        if (playerAttacksFirst) 
        {
            playerCombatTurn(hero, foe); // Includes attack flow
            if (foe.getHealth() > 0) 
                enemyAttack(foe); // Enemy attacks back
        }
        else 
        {
            enemyAttack(foe); // Enemy attacks first
            if (hero.currentHealth > 0)
                playerCombatTurn(foe);
        }
        currentRound++;
    }
    checkGameOver(Player hero);
    if (checkDeadEnemy(Enemy& foe)) //If the enemy is dead.
    {
        clearTile(hero.coordinates);
        overWorld();
    }
}

void initiatePlayer() 
{
    // Create player with default starting stats
    Player p(
        6,     // maxHealth
        3,     // maxMana
        51,    // accuracy
        0,     // evasion
        1,     // initiative
        2,     // damage
        0, 0, 0); // start position x=0, y=0

    p.currentHealth = p.maxHealth;
    p.currentMana = p.maxMana;

    Player = p;  // Assign to global player
    maps[0].generateMap1(); // Generate map 0
    currentMapIndex = 0;

    std::cout "! Your journey begins...\n";
    overWorld(p);
}

void overWorld(Player& hero) 
{
    while (true)
    {
        std::cout << "\n=== Overworld Menu ===\n";
        std::cout << "1. Move\n";
        std::cout << "2. Show Current Map\n";
        std::cout << "3. Heal (Cost: 3 Mana)\n";
        std::cout << "4. Save Game\n";
        std::cout << "5. Quit Game\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        clearInput();
        switch (choice)
        {
        case 1:
            movePlayer();
            break;
        case 2:
            showMap(maps[hero.coordinates[2]], hero);
            break;
        case 3:
            if (hero.currentMana < 3) 
            {
                std::cout << "Not enough mana to heal.\n";
            }
            else 
            {
                int missing = hero.maxHealth - hero.currentHealth;
                int healAmount = missing / 2;
                hero.currentHealth += healAmount;
                hero.currentMana -= 3;
                std::cout << "You heal for " << healAmount << " HP. Current HP: "
                    << hero.currentHealth << "/" << hero.maxHealth << "\n";
            }
            break;
        case 4:
            savePlayer(hero);
            maps[hero.coordinates[2]].saveMap(hero.coordinates[2]);
            break;
        case 5:
            std::cout << "Exiting game...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            exit(0);
        default:
            std::cout << "Invalid option. Try again.\n";
            break;
        }
    }
}


void checkGameOver(Player& hero)
{
    if (hero.currentHealth <= 0)
    {
        std::cout << "\nYou have died.";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        exit(0); // In the future, it sends the player to the main menu.
    }
}

bool checkDeadEnemy(Player& hero, Enemy& foe) // Added '&' to refer to the original enemy object.
{
    if (foe.health <= 0) // Dead enemy.
    {
        std::cout << "\n" << foe.name << " has been defeated.";
        hero.experience += foe.bounty;
        std::cout << "\nYou gain " << foe.bounty << " Experience Points."; // Fixed concatenation and formatting.
        return true;
    }
    return false; // This means the enemy is still alive.
}

void checkGameCompletion() 
{
    Tile& bossTile = maps[4].grid[8][7]; // Assuming boss is always at (8,7) on map 4
    if (bossTile.type == "Boss" && bossTile.cleared) 
    {
        std::cout << "\nCongratulations, you completed Cave Delver!\n";
        std::cout << "Thanks for playing. Try another build.\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
        exit(0);
    }
}


