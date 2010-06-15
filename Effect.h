#ifndef EFFECT_H
#define EFFECT_H

#include <SFML/Graphics.hpp>
#include "Particle.h"

class Effect {
public:
  Effect(const sf::Image& img, Vector2D offset, int num = 20, Vector2D pos = Vector2D(0,0), Vector2D posVar = Vector2D(0,0), Vector2D vel = Vector2D(0,0), Vector2D velVar = Vector2D(0,0), Vector2D acc = Vector2D(0,0), float life = 30, bool repeat = true);
  Effect();
  
  void SetParticle(Particle & p);
  void SetPosition(Vector2D pos) { this->pos = pos; };
  void Play();
  
  void Update(float time, const Map& map);
  void Draw(sf::RenderWindow &window);
  
private:
  vector<Particle> particles;
  vector<Particle> actives;
  
  Vector2D pos;
  Vector2D vel;
  Vector2D posVar;
  Vector2D velVar;
  Vector2D acc;
  bool repeat;
};


class Smoke : public Effect {
public:
  Smoke(const sf::Image& img, Vector2D offset, int num = 50, Vector2D pos = Vector2D(0,0)): Effect(img, offset, num, pos, Vector2D(2,2), Vector2D(0,0), Vector2D(20,0), Vector2D(0, -50.f)) {};
  
  void Update(float time, const Map& map);
};


#endif
