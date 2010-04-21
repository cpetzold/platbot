#include "Map.h"

Map::Map(sf::Image &mask, sf::Image &terrain) : sf::Sprite() {
  this->mask = mask;
  this->terrain = terrain;
  this->Generate();
}

Map::~Map() {
  // clean up yo!
}

void Map::SetMask(sf::Image& mask) {
  this->mask = mask;
}

void Map::SetTerrain(sf::Image& terrain) {
  this->terrain = terrain;
}

void Map::Generate() {
  
  sf::Image * image = new sf::Image(this->mask.GetWidth(), this->mask.GetHeight());
  
  int xRepeat = (image->GetWidth() / 256)+1;
  int yRepeat = (image->GetHeight() / 256)+1;
  
  for (int i = 0; i < yRepeat; i++) {
    for (int j = 0; j < xRepeat; j++) {
      image->Copy(this->terrain, 256*j, 256*i, sf::IntRect(0, 16, 256, 256+16), true);
    }
  }
  
  for (int i = 0; i < image->GetWidth(); i++) {
    for (int j = 0; j < image->GetHeight(); j++) {
      if (this->mask.GetPixel(i, j).a == sf::Color(0, 0, 0, 0).a) {
        image->SetPixel(i, j, sf::Color(0, 0, 0, 0));
      }
    }
  }
  
  int xGrass = 0;
  int xBottom = 64;
  int y = 0;
  int yStart = 0;
  int yEnd = 0;
  
  for (int x = 0; x < image->GetWidth(); x++) {
    while (y < image->GetHeight()-1) {
      while (image->GetPixel(x, y) == sf::Color(0, 0, 0, 0)
             && y < image->GetHeight()-1) {
        y++;
      }
      yStart = y;
      
      while (image->GetPixel(x, y) != sf::Color(0, 0, 0, 0)
             && y < image->GetHeight()-1) {
        y++;
      }
      yEnd = y;
      
      if (xGrass >= 64) xGrass = 0;
      if (xBottom >= 128) xBottom = 64;
      
      if ((yEnd-yStart) / 2 > 0) {
        image->Copy(this->terrain, x, yStart, sf::IntRect(xGrass, 0, xGrass+1, 16), true);
        image->Copy(this->terrain, x, yEnd-16, sf::IntRect(xBottom, 0, xBottom+1, 16), true);
        
        bool notBottom = false;
        bool notTop = false;
        
        for (int n = 15; n >= 0; n--) {
          if (this->terrain.GetPixel(xGrass, n).a == sf::Color(0, 0, 0, 0).a) { // grass is transparent here
            if (notBottom) {
              image->SetPixel(x, yStart+n, sf::Color(0, 0, 0, 0));
            }
          } else if (!notBottom) {
            notBottom = true;
          }
          
          if (this->terrain.GetPixel(xBottom, 15-n).a == sf::Color(0, 0, 0, 0).a) { // bottom is transparent here
            if (notTop) {
              image->SetPixel(x, yEnd-n-1, sf::Color(0, 0, 0, 0));
            }
          } else if (!notTop) {
            notTop = true;
          }
        }
        
      }
    }
    
    xGrass++;
    xBottom++;
    y = 0;
  }
  
  this->SetImage(*image);
}

sf::IntRect Map::GetAABB() {
  sf::Vector2f pos = this->TransformToGlobal(sf::Vector2f(0, 0));
  sf::Vector2f size = this->GetSize();
  return sf::IntRect(static_cast<int> (pos.x),
                     static_cast<int> (pos.y),
                     static_cast<int> (pos.x + size.x),
                     static_cast<int> (pos.y + size.y));
}