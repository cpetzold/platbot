#ifndef TILE_H
#define TILE_H

#include <Gosu/Gosu.hpp>

#include "Vec.h"
#include "Rect.h"

#include <string>
#include <iostream>
using namespace std;

class Tile : public Gosu::Image {
private:
  Vec pos;
  bool solid;
  bool visible;
  float friction;

public:
  Tile(Gosu::Graphics &graphics, const std::wstring &filename, unsigned srcX, unsigned srcY, unsigned size, bool sol, float frict = .5) : Image(graphics, filename, srcX*size, srcY*size, size, size, true), solid(sol), visible(true), friction(frict){};

  void setPosition(Vec pos) { this->pos = pos; };
  Vec getPosition() const { return this->pos; };
  bool isSolid() const{ return this->solid; };
  bool isVisible() const { return this->visible; };
  float getFriction() const {return this->friction; };
  Rect getAABB() const;

};

#endif
