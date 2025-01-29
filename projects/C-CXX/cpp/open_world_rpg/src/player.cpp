// player.cpp
#include "../include/Player.h"
#include "../include/enemy.h"
#include <iostream>

Player::Player(const std::string &playerName, int playerHealth,
               int playerAttack)
    : name(playerName), health(playerHealth), attack(playerAttack) {}

void Player::attackEnemy(Enemy &enemy) {
  int damage = rand() % attack + 1;
  std::cout << name << " attacks " << enemy.name << " for " << damage
            << " damage!" << std::endl;
  enemy.health -= damage;
}

void Player::heal(int amount) {
  health += amount;
  std::cout << name << " heals for " << amount << " health!" << std::endl;
}

void Player::displayStats() {
  std::cout << "Player: " << name << " | Health: " << health
            << " | Attack: " << attack << std::endl;
}
