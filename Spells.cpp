if (selected.name == "Heal") {
    int missing = player.maxHealth - player.currentHealth;
    int healAmount = missing / 2;
    player.currentHealth += healAmount;
    std::cout << "You heal for " << healAmount << " HP (now at " << player.currentHealth << "/" << player.maxHealth << ")\n";
}
else if (selected.name == "Fireball") {
    int damage = 7;
    enemy.setHealth(enemy.getHealth() - damage);
    std::cout << "You hurl a fireball for " << damage << " damage!\n";
    std::cout << enemy.getName() << " HP left: " << enemy.getHealth() << "\n";

    if (enemy.getHealth() <= 0) {
        std::cout << "Enemy defeated! +" << enemy.getBounty() << " XP.\n";
        player.experience += enemy.getBounty();
        maps[currentMapIndex].grid[player.coordinates[0]][player.coordinates[1]].cleared = true;
        return true; // end combat
    }
}
else {
    std::cout << "The spell's effect is not implemented yet.\n";
}

else if (selected.name == "Bless") {
    player.blessTurns = 5;
    std::cout << "You feel empowered! +3 Damage and 50% damage taken for 5 turns.\n";
}
else if (selected.name == "Sleep") {
    int roll = randomPercent();
    if (roll < 60) {
        enemy.sleepTurns = 3;
        std::cout << "Sleep successful! " << enemy.getName() << " is stunned for 3 turns.\n";
    }
    else {
        std::cout << "Sleep failed!\n";
    }
}
else if (selected.name == "Reflect Damage") {
    player.reflectTurns = 4;
    std::cout << "A mirror aura surrounds you! Damage will reflect for 4 turns.\n";
}

/**int clamp(int value, int min, int max)
{
    return std::max(min, std::min(value, max)); // Helper: Clamp within range
} */

