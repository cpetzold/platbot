#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include "json/reader.h"
#include "json/writer.h"
#include "json/elements.h"

#include "Tile.h"
#include "Resources.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

class Map {
private:
  sf::Image* tileset;
  int tilesize;
  Vector2D dim;
  vector<vector<Tile> > tiles;


public:

  Map();
  Map(string filename, Resources &data);
  //~Map();
  const Tile& at(int x, int y) const{
      return tiles.at(y).at(x);
      } ;
  void Draw(sf::RenderWindow &window);

  int getTileSize() const{return tilesize;};

};

#endif
