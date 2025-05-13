#pragma once

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
    Spell(const std::string& name, int manaCost, const std::string& description);
    void print() const;
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
    int coordinates[3]; // [x, y, z]
    std::vector<Spell> spells;

    Player(int maxHealth, int maxMana,
        int accuracy, int evasion,
        int initiative, int damage,
        int x = 0, int y = 0, int z = 0,
        int experience = 0, int level = 1);
    void addSpell(const Spell& spell);
    void printStats() const;
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
    Enemy(const std::string& name, int health, int accuracy, int evasion, int initiative, int damage, int bounty);
    virtual void print() const;
    virtual ~Enemy() = default;
};

class Boss : public Enemy
{
private:
    std::string special;

public:
    Boss(const std::string& name, int health, int accuracy, int evasion, int initiative, int damage, int bounty, const std::string& special);
    void print() const override;
};