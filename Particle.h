#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include "Dynamic.h"

class Particle : public Dynamic {
public:
  Particle(const sf::Image& img, Vector2D offset, float life = 100, Vector2D acc = Vector2D(0,0), Vector2D pos = Vector2D(0,0), Vector2D vel = Vector2D(0,0));
  Particle();
  void Update(float time, const Map& map);
  bool Dead() { return this->life <= 0; };
  
  void Reset(Vector2D pos, Vector2D vel);
  
private:
  float startLife;
  float life;
  
};
#endif
