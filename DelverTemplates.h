#pragma once // Use include guards or #pragma once

#include <vector>
#include <string>
#include "DelverClasses.h" // Make sure this includes the definitions for Spell, Enemy, Boss classes

// --- Spell Declarations ---
// Use 'extern' to declare that these objects are defined elsewhere (.cpp file)
extern Spell spell_heal;
extern Spell spell_fireball;
extern Spell spell_bless;
extern Spell spell_sleep;
extern Spell spell_reflect;

// --- Spell Collection Declaration ---
extern std::vector<Spell> playerSpells; // Declares the vector exists

// --- Enemy Declarations ---
extern Enemy goblin;
extern Enemy orc;
extern Enemy ogre;
extern Enemy troll;
extern Enemy goliath; // Note: Renamed the second Troll from your previous data

// --- Boss Declarations ---
extern Boss hugeBear;
extern Boss golem;
extern Boss spider; // Assuming class name consistency
extern Boss wyvern;
extern Boss hydra;

// Consider wrapping these in a namespace to avoid polluting the global scope
// namespace GameData {
//     extern Spell spell_heal;
//     // ... etc ...
// }