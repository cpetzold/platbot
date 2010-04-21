#ifndef ROPE_H
#define ROPE_H

#include <string>
#include <iostream>
using namespace std;

#include "Player.h"
#include "Vector2D.h"
#include <SFML/Graphics.hpp>

class Rope : vector<Vector2D> {
private:
  int maxLength;
  Player * player;
  sf::Shape * lines;
  
public:
  
  Rope(Player* player, int maxLength = 30);
  ~Rope();
  
  void Shoot(float angle);
  void Update(float t);
  sf::Shape * GetLines();
  
};

#endif