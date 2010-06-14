#include "Particle.h"

Particle::Particle(const sf::Image& img, Vector2D offset, float life, Vector2D acc, Vector2D pos, Vector2D vel) : Dynamic(img, sf::Vector2f(pos.x, pos.y), 16, 16, 7) {
  this->startLife = life;
  this->life = life;
  
  if (offset.x >= 0) {
    this->frame = offset.x;
    this->frameSpeed = 0;
  }
  this->frameState = offset.y;

  
  this->setPosition(pos);
  this->setVelocity(vel);
  this->setAcceleration(acc);
}

void Particle::Reset(Vector2D pos, Vector2D vel) {
  this->life = this->startLife;
  this->setPosition(pos);
  this->setVelocity(vel);
  this->SetScale(1, 1);
}

void Particle::Update(float time, const Map& map) {
  this->life -= time*10;
  int a = 255 * (this->life / this->startLife);
  this->SetColor(sf::Color(255,255,255,a));
  this->Dynamic::update(time, map);
}
