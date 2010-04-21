#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Vector2D.h"

#include <string>
#include <iostream>
using namespace std;

class Player : sf::Sprite {
private:
  Vector2D pos;
  Vector2D vel;
  Vector2D acc;
  Vector2D prov;
  
  sf::Image * mask;
  Vector2D off;
  
public:
  
  Player(sf::Image & img, sf::Image & mask, sf::Vector2f pos = sf::Vector2f(100, 0));
  ~Player();
  
  void Update(float t, Map & m);
  
  sf::IntRect GetAABB();
  
  bool IsColliding(Map * m);
  void HandleCollision();
  
};

#endif