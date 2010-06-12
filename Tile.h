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
  float friction;

public:
  Tile() : sf::Sprite(), solid(false), visible(false) {};
  Tile(const sf::Image& img, bool sol, float frict = .5) : sf::Sprite(img), solid(sol), visible(true), friction(frict){};

  bool IsSolid() const{ return this->solid; } ;
  bool IsVisible() const { return this->visible; } ;
  float getFriction() const {return this->friction;};
  sf::Rect<float> getAABB() const;

};

#endif
