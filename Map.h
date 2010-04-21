#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
using namespace std;

class Map : sf::Sprite {
private:
  sf::Image* image;
  sf::Image mask;
  sf::Image terrain;
  
public:
  
  Map();
  Map(sf::Image& mask, sf::Image& terrain);
  ~Map();
  
  void SetMask(sf::Image& mask);
  void SetTerrain(sf::Image& terrain);
  
  sf::IntRect GetAABB();
  
  void Generate();
  
};

#endif