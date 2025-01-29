// main.cpp
#include <iostream>
#include "Player.h"
#include "enemy.h"

int main() {
    Player player("Hero", 100, 10);
    Enemy enemy("Goblin", 50, 5);

    player.displayStats();
    enemy.displayStats();

    enemy.attackPlayer(player);
    player.displayStats();

    return 0;
}

