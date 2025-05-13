#include "GameStates.h"


void playerAttack(Enemy& foe, Player& hero)
{
    int chance = hero.accuracy - foe.evasion;
    if (randomChance(chance))
    {
        std::cout << "\n You Hit!";
        foe.health -= hero.damage;
        std::cout << "\n" << foe.name << " takes " << hero.damage << " damage (HP left: " << foe.health << ")";
    }
    else
        std::cout << "You Missed!\n";
}

void clearTile(Tile& tile)
{
    tile.cleared = true;
}

void enemyAttack(Enemy& foe, Player& hero)
{
    int chance = foe.accuracy - hero.evasion;
    if (randomChance(chance))
    {
        std::cout << "\n You got Hit!";
        hero.currentHealth -= foe.damage;
        std::cout << "\n You take " << foe.damage << " damage (HP left: " << hero.currentHealth << ")";
    }
    else
        std::cout << foe.name << "\n Missed!";
}

Enemy getEnemyForTile(int location[3])
{
    int x = location[0];
    int y = location[1];
    int z = location[2];
    Tile& tile = cave.getCurrentMap(z).getTile(x, y);
    const std::string& type = tile.type;
    if (type == "Enemy")
    {
        if (z == 0) return goblin;
        if (z == 1) return orc;
        if (z == 2) return ogre;
        if (z == 3) return troll;
        if (z == 4) return goliath;
    }
    else if (type == "Boss")
    {
        if (z == 0) return hugeBear;
        if (z == 1) return golem;
        if (z == 2) return spider;
        if (z == 3) return wyvern;
        if (z == 4) return hydra;
    }
    std::cerr << "No valid enemy found at tile (" << x << "," << y << "," << z << ")\n";
    return goblin; // Fallback
}

void checkGameOver(Player& hero)
{
    if (hero.currentHealth <= 0)
    {
        std::cout << "\nYou have died.";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        mainMenuLoop();
    }
}

bool checkDeadEnemy(Player& hero, Enemy& foe)
{
    if (foe.health <= 0)
    {
        std::cout << "\n" << foe.name << " has been defeated.";
        hero.experience += foe.bounty;
        std::cout << "\nYou gain " << foe.bounty << " Experience Points.";
        return true;
    }
    return false;
}

bool playerGoesFirst(int playerInit, int enemyInit)
{
    if (playerInit > enemyInit) return true;
    if (enemyInit > playerInit) return false;
    return randomChance(50);
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
        if (randomChance(50))
        {
            std::cout << "You successfully fled.\n";
            overWorld(hero);
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
        playerCombatTurn(hero, foe);
    }
}

void spellMenu(Player& hero, Enemy& foe)
{
    std::cout << "\n=== Spellbook ===";
    for (size_t i = 0; i < hero.spells.size(); ++i)
    {
        const Spell& s = hero.spells[i];
        std::cout << "\n " << i + 1 << ". " << s.name << " (Cost: " << s.manaCost << ") - " << s.description << "";
    }
    std::cout << "\n 0. Cancel";
    std::cout << "\n Select a spell: ";

    int choice;
    std::cin >> choice;
    clearInput();

    if (choice == 0) playerCombatTurn(hero, foe);
    if (choice < 0 || choice > static_cast<int>(hero.spells.size()))
    {
        std::cout << "\n Invalid selection.";
        spellMenu(hero, foe);
    }
    Spell& selected = hero.spells[choice - 1];
    if (hero.currentMana < selected.manaCost)
        std::cout << "\n Not enough mana to cast " << selected.name << ".";
    hero.currentMana -= selected.manaCost;
    std::cout << "You cast " << selected.name << "!\n";

    // TODO: Implement spell effect by name (in next step)
    std::cout << "The spell effect takes place.\n";
}

void handleCombat(Player& hero, Enemy& foe)
{
    int currentRound = 1;
    bool playerAttacksFirst = playerGoesFirst(hero.initiative, foe.initiative);
    while (hero.currentHealth > 0 && foe.health > 0)
    {
        std::cout << "\n Round " << currentRound << std::endl;
        if (playerAttacksFirst)
        {
            playerCombatTurn(hero, foe);
            if (foe.health > 0)
                enemyAttack(foe, hero);
        }
        else
        {
            enemyAttack(foe, hero);
            if (hero.currentHealth > 0)
                playerCombatTurn(hero, foe);
        }
        currentRound++;
    }
    checkGameOver(hero);
    if (checkDeadEnemy(hero, foe))
    {
        int x = hero.coordinates[0];
        int y = hero.coordinates[1];
        int z = hero.coordinates[2];
        Tile& tile = cave.getCurrentMap(z).getTile(x, y);
        overWorld(hero);
    }
}

void initiatePlayer()
{
    Player p(
        6,
        3,
        51,
        0,
        1,
        2,
        0, 0, 0
    );

    p.currentHealth = p.maxHealth;
    p.currentMana = p.maxMana;

    cave.getCurrentMap(0).generateMap1();
    cave.getCurrentMap(1).generateMap2();
    cave.getCurrentMap(2).generateMap3();
    cave.getCurrentMap(3).generateMap4();
    cave.getCurrentMap(4).generateMap5();

    std::cout << "! Your journey begins...\n";
    overWorld(p);
}

void checkGameCompletion()
{
    Tile& bossTile = cave.getCurrentMap(4).getTile(8, 7);
    if (bossTile.type == "Boss" && bossTile.cleared)
    {
        std::cout << "\nCongratulations, you completed Cave Delver!\n";
        std::cout << "Thanks for playing. Try another build.\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
        mainMenuLoop();
    }
}

void handlePostMovementEvent(Player& hero)
{
    Tile& tile = cave.getCurrentMap(hero.coordinates[2]).getTile(hero.coordinates[0], hero.coordinates[1]);
    std::string& type = tile.type;
    bool reached = tile.cleared;

    std::cout << "\nYou stepped on: " << type;

    if (type == "Empty") {
        reached = true;
    }
    else if (type == "Enemy" || type == "Boss") {
        if (!reached) {
            std::cout << "\nCombat begins!\n";
            Enemy foe = getEnemyForTile(hero.coordinates);
            handleCombat(hero, foe);
        }
    }
    else if (type == "Trap") {
        if (!reached) {
            std::cout << "\nIt's a trap! You take 4 damage!\n";
            hero.currentHealth -= 4;
            checkGameOver(hero);
        }
        reached = true;
    }
    else if (type == "Rest") {
        if (!reached) {
            std::cout << "\nRest spot! +5 Health and Mana.\n";
            hero.currentHealth = std::clamp(hero.currentHealth + 5, 0, hero.maxHealth);
            hero.currentMana = std::clamp(hero.currentMana + 5, 0, hero.maxMana);
        }
        reached = true;
    }
    else if (type == "Treasure") {
        if (!reached) {
            std::cout << "\nYou found a treasure! +2 Damage, +1 Initiative.\n";
            hero.damage += 2;
            hero.initiative += 1;
        }
        reached = true;
    }
    else if (type == "Ladder") {
        std::cout << "\nYou've found the ladder. Ascend to next floor? (Y/N): ";
        char response;
        std::cin >> response;
        clearInput();
        reached = true;
        if (toupper(response) == 'Y') {
            hero.coordinates[2] += 1;
            hero.coordinates[0] = 0;
            hero.coordinates[1] = 0;
            std::cout << "\nYou ascend to map " << (hero.coordinates[2]) << "!\n";
        }
    }

    tile.cleared = reached;
    checkGameCompletion();
}

void movePlayer(Player& hero, const std::string& dir)
{
    std::string input = dir;
    for (auto& c : input) c = std::toupper(c);

    int newX = hero.coordinates[0];
    int newY = hero.coordinates[1];

    if (input == "N") newY += 1;
    else if (input == "S") newY -= 1;
    else if (input == "E") newX += 1;
    else if (input == "W") newX -= 1;
    else if (input == "NE") { newX += 1; newY += 1; }
    else if (input == "NW") { newX -= 1; newY += 1; }
    else if (input == "SE") { newX += 1; newY -= 1; }
    else if (input == "SW") { newX -= 1; newY -= 1; }
    else {
        std::cout << "Invalid movement direction.\n";
        return;
    }

    if (newX < 0 || newX >= MAP_SIZE || newY < 0 || newY >= MAP_SIZE) {
        std::cout << "You cannot move off the map.\n";
        return;
    }

    hero.coordinates[0] = newX;
    hero.coordinates[1] = newY;
    handlePostMovementEvent(hero);
}

void overWorld(Player& hero)
{
    while (true)
    {
        std::cout << "\n=== Overworld Menu ===\n";
        std::cout << "Enter a direction (N/S/E/W/NE/NW/SE/SW), or:\n";
        std::cout << "1. Show Current Map\n";
        std::cout << "2. Heal (Cost: 3 Mana)\n";
        std::cout << "3. Show Stats\n";
        std::cout << "4. Save Game\n";
        std::cout << "5. Quit Game\n";
        std::cout << "Input: ";

        std::string input;
        std::cin >> input;
        clearInput();

        if (!isdigit(input[0])) {
            movePlayer(hero, input);
            continue;
        }

        int choice = std::stoi(input);

        switch (choice)
        {
        case 1:
            cave.getCurrentMap(hero.coordinates[2]).printMap(hero.coordinates[0], hero.coordinates[1]);
            break;
        case 2: // TODO: Replace with spell selection
            if (hero.currentMana < 3)
                std::cout << "Not enough mana to heal.\n";
            else {
                int missing = hero.maxHealth - hero.currentHealth;
                int healAmount = missing / 2;
                hero.currentHealth += healAmount;
                hero.currentMana -= 3;
                std::cout << "You heal for " << healAmount << " HP. Current HP: "
                    << hero.currentHealth << "/" << hero.maxHealth << "\n";
            }
            break;
        case 3:
            hero.printStats();
            break;
        case 4:
            savePlayer(hero);
            cave.getCurrentMap(hero.coordinates[2]).saveMap();
            break;
        case 5:
            std::cout << "\nExiting game...";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            exit(0);
        default:
            std::cout << "\nInvalid option. Try again.\n";
            break;
        }
    }
}
