#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

#include "Vector2D.h"

#include <string>
#include <iostream>
using namespace std;

class Tile : public sf::Sprite {
private:
  bool solid;
  bool visible;
  
public:
  Tile() : sf::Sprite(), solid(false), visible(false) {};
  Tile(const sf::Image& img, bool sol) : sf::Sprite(img), solid(sol), visible(true) {};
  
  bool IsSolid() { return this->solid; };
  bool IsVisible() { return this->visible; };
  
};

#endif