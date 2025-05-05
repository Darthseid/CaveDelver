#include <iostream>
#include <string>
#include <vector>

// --- Spell Class ---
class Spell 
{
public:
    std::string name;
    int manaCost;
    std::string description;
    Spell(const std::string& name, int manaCost, const std::string& description)
        : name(name), manaCost(manaCost), description(description) 
    {

    }
    void print() const 
    {
        std::cout << "Spell: " << name << ", Mana Cost: " << manaCost
            << ", Description: " << description << "\n";
    }
};

class Player
{
public:
    int maxHealth;
    int currentHealth;
    int maxMana;
    int currentMana;
    int accuracy;
    int evasion;
    int initiative;
    int damage;
    int experience;
    int level;
    int coordinates[2]; // [x, y, z]
    std::vector<Spell> spells;

    Player(int maxHealth, int maxMana,
        int accuracy, int evasion,
        int initiative, int damage,
        int x = 0, int y = 0, int experience, int level)
        : maxHealth(maxHealth), currentHealth(maxHealth),
        maxMana(maxMana), currentMana(maxMana),
        accuracy(accuracy), evasion(evasion),
        initiative(initiative), damage(damage), experience(experience), level(level)
    {
        coordinates[0] = x;
        coordinates[1] = y;
    }

    void addSpell(const Spell& spell)
    {
        spells.push_back(spell);
    }

    void printStats() const
    {
        std::cout << "Health: " << currentHealth << "/" << maxHealth << "\n"
            << "Mana: " << currentMana << "/" << maxMana << "\n"
            << "Accuracy: " << accuracy << ", Evasion: " << evasion
            << ", Initiative: " << initiative << ", Damage: " << damage << "\n" << ", Level: " << level << ", Experience, " << experience
            << "Position: (" << coordinates[0] << ", " << coordinates[1] << ")\n"
            << "Spells:\n";
        for (const auto& spell : spells)
            spell.print();
    }
};

class Enemy 
{
public:
    std::string name;
    int health;
    int accuracy;
    int evasion;
    int initiative;
    int damage;
    int bounty; // experience reward

public:
    Enemy(const std::string& name, int health, int accuracy, int evasion, int initiative, int damage, int bounty)
        : name(name), health(health), accuracy(accuracy), evasion(evasion),
        initiative(initiative), damage(damage), bounty(bounty) {
    }

    virtual void print() const 
    {
        std::cout << "Enemy: " << name << "\n"
            << "Health: " << health << "\n"
            << "Accuracy: " << accuracy << "\n"
            << "Evasion: " << evasion << "\n"
            << "Initiative: " << initiative << "\n"
            << "Damage: " << damage << "\n"
            << "Bounty (XP): " << bounty << "\n";
    }
    virtual ~Enemy() = default;
};

class Boss : public Enemy 
{
private:
    std::string special;

public:
    Boss(const std::string& name, int health, int accuracy, int evasion, int initiative, int damage, int bounty, const std::string& special)
        : Enemy(name, health, accuracy, evasion, initiative, damage, bounty), special(special) {
    }

    void print() const override 
    {
        std::cout << "BOSS: " << name << "\n"
            << "Health: " << health << "\n"
            << "Accuracy: " << accuracy << "\n"
            << "Evasion: " << evasion << "\n"
            << "Initiative: " << initiative << "\n"
            << "Damage: " << damage << "\n"
            << "Bounty (XP): " << bounty << "\n"
            << "Special Ability: " << special << "\n";
    }
};