#include "DelverClasses.h"
#include <iostream>

// --- Spell Class ---
Spell::Spell(const std::string& name, int manaCost, const std::string& description)
    : name(name), manaCost(manaCost), description(description)
{
}

void Spell::print() const
{
    std::cout << "Spell: " << name << ", Mana Cost: " << manaCost
        << ", Description: " << description << "\n";
}

// --- Player Class ---
Player::Player(int maxHealth, int maxMana,
    int accuracy, int evasion,
    int initiative, int damage,
    int x, int y, int z,
    int experience, int level)
    : maxHealth(maxHealth), currentHealth(maxHealth),
    maxMana(maxMana), currentMana(maxMana),
    accuracy(accuracy), evasion(evasion),
    initiative(initiative), damage(damage),
    experience(experience), level(level)
{
    coordinates[0] = x;
    coordinates[1] = y;
    coordinates[2] = z;
}

void Player::addSpell(const Spell& spell)
{
    spells.push_back(spell);
}

void Player::printStats() const
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

// --- Enemy Class ---
Enemy::Enemy(const std::string& name, int health, int accuracy, int evasion, int initiative, int damage, int bounty)
    : name(name), health(health), accuracy(accuracy), evasion(evasion),
    initiative(initiative), damage(damage), bounty(bounty)
{
}

void Enemy::print() const
{
    std::cout << "Enemy: " << name << "\n"
        << "Health: " << health << "\n"
        << "Accuracy: " << accuracy << "\n"
        << "Evasion: " << evasion << "\n"
        << "Initiative: " << initiative << "\n"
        << "Damage: " << damage << "\n"
        << "Bounty (XP): " << bounty << "\n";
}

// --- Boss Class ---
Boss::Boss(const std::string& name, int health, int accuracy, int evasion, int initiative, int damage, int bounty, const std::string& special)
    : Enemy(name, health, accuracy, evasion, initiative, damage, bounty), special(special)
{
}

void Boss::print() const
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