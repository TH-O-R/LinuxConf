// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
  std::string name;
  int health;
  int attack;

  Enemy(const std::string &enemyName, int enemyHealth, int enemyAttack);
  void attackPlayer(class Player &player);
  void displayStats();
};

#endif
