#include "DelverHelpers.h"
#include "DelverClasses.h"
#include "Spells.h"
#include "DelverMap.h"
#include "GameStates.h"

extern Cave cave;

void savePlayer(const Player& hero)
{
    std::ofstream out("Player.txt");
    if (!out.is_open())
    {
        std::cerr << "Error: Could not write Player.txt\n";
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
    cave.getCurrentMap(hero.coordinates[2]).saveMap();
    out.close();
    std::cout << "Player saved successfully.\n";
}

void loadPlayer()
{
    std::ifstream in("Player.txt");
    if (!in.is_open())
    {
        std::cerr << "Error: Could not open Player.txt\n";
        exit(1);
    }

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
    in.ignore();

    std::vector<Spell> spells;
    for (int i = 0; i < spellCount; ++i)
    {
        std::string spellName, description;
        int manaCost;

        std::getline(in, spellName);
        in >> manaCost;
        in.ignore();
        std::getline(in, description);

        spells.emplace_back(spellName, manaCost, description);
    }

    Player player(maxHealth, maxMana, accuracy, evasion, initiative, damage, x, y);
    player.currentHealth = currentHealth;
    player.currentMana = currentMana;
    player.coordinates[2] = z;
    player.spells = spells;

    cave.getCurrentMap(z).loadMap();
    std::cout << "Player loaded: " << "\n";
    overWorld(player);
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
        checkLevelUp(hero);
    }
}
