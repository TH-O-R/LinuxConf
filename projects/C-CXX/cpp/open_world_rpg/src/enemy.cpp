// enemy.cpp
#include "../include/enemy.h"
#include "../include/Player.h"
#include <iostream>

Enemy::Enemy(const std::string &enemyName, int enemyHealth, int enemyAttack)
    : name(enemyName), health(enemyHealth), attack(enemyAttack) {}

void Enemy::attackPlayer(Player &player) {
  int damage = rand() % attack + 1;
  std::cout << name << " attacks " << player.name << " for " << damage
            << " damage!" << std::endl;
  player.health -= damage;
}

void Enemy::displayStats() {
  std::cout << "Enemy: " << name << " | Health: " << health
            << " | Attack: " << attack << std::endl;
}
