#ifndef MAP_H
#define MAP_H

#include "json/reader.h"
#include "json/writer.h"
#include "json/elements.h"
using namespace json;

#include "Tile.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

class Map {
private:
  wstring tileset;
  int tilesize;
  Vec dim;
  vector<vector<Tile> > tiles;


public:

  Map();
  Map(Gosu::Graphics& graphics, wstring filename);

  const Tile& at(int x, int y) const{
      return tiles.at(y).at(x);
    } ;
  void draw();

  int getTilesize() const{return tilesize;};
  int getWidth() const {return dim.x;};
  int getHeight() const {return dim.y;};

};

#endif
