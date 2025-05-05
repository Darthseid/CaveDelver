// --- Spells ---
#include <vector>
#include "DelverClasses.h"

Spell spell_heal("Heal", 3, "Player recovers 50% of Missing Health.");
Spell spell_fireball("Fireball", 6, "Player deals 7 Damage to Enemy");
Spell spell_bless("Bless", 9, "Player deals +3 Damage and takes Half Damage for next 5 turns.");
Spell spell_sleep("Sleep", 12, "Target enemy is stunned for 3 turns. 60% chance of success.");
Spell spell_reflect("Reflect Damage", 15, "Enemy takes mirrored damage. Lasts 4 turns.");

// --- Spell Collection for Player ---
std::vector<Spell> playerSpells = 
{
    spell_heal,
    spell_fireball,
    spell_bless,
    spell_sleep,
    spell_reflect
};


// --- Enemies ---
Enemy goblin("Goblin", 2, 40, 0, 0, 1, 1);
Enemy orc("Orc", 5, 45, 5, 1, 2, 3);
Enemy ogre("Ogre", 8, 50, 8, 2, 3, 5);
Enemy troll("Troll", 11, 55, 11, 3, 4, 7);
Enemy goliath("Goliath", 14, 65, 14, 4, 5, 9);

// --- Bosses ---
Boss hugeBear("Huge Bear", 8, 50, 10, 7, 3, 12, "First_Strike");
Boss golem("Golem", 14, 60, 14, 3, 5, 18, "Anti-Mage");
Boss spider("Giant Spider", 20, 70, 18, 4, 7, 24, "Poison_Bite");
Boss wyvern("Wyvern", 26, 80, 22, 5, 9, 30, "Camouflage");
Boss hydra("Hydra", 32, 90, 26, 6, 8, 0, "Multi-Heads");
