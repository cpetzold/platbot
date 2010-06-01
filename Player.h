#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Vector2D.h"

#include <string>
#include <iostream>
using namespace std;

class Player : public sf::Sprite {
private:
  Vector2D pos;
  Vector2D vel;
  Vector2D acc;
  Vector2D accd;
  Vector2D prov;
  Vector2D last;
  
  int fric;
  
  sf::Image * mask;
  Vector2D off;
  
public:
  
  Player();
  Player(sf::Image & img, sf::Image & mask, sf::Vector2f pos = sf::Vector2f(100, 0));
  ~Player();
  
  void Update(float t, Map & m);
  
  void Jump();
  void ApplyForce(Vector2D f);
  
  sf::IntRect GetAABB(Vector2D pos);
  
  bool IsColliding(Map * m);
  void HandleCollision();
  
  void Debug(sf::RenderWindow & window);
  
};

#endif