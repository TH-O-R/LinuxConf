// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player {
public:
  std::string name;
  int health;
  int attack;
  std::vector<std::string> inventory;

  Player(const std::string &playerName, int playerHealth, int playerAttack);
  void attackEnemy(class Enemy &enemy);
  void heal(int amount);
  void displayStats();
};

#endif
