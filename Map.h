/*
 *  Map.h
 *  ropebot
 *
 *  Created by Conner Petzold on 4/17/10.
 *  Copyright 2010 CSU. All rights reserved.
 *
 */

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
using namespace std;

class Map : sf::Image {
private:
  sf::Image* image;
  sf::Image mask;
  sf::Image terrain;
  
public:
  
  Map();
  Map(sf::Image& mask, sf::Image& terrain);
  ~Map();
  
  sf::Image* GetImage();
  sf::Sprite GetSprite();
  
  void SetMask(sf::Image& mask);
  void SetTerrain(sf::Image& terrain);
  void Generate();
  
};

#endif