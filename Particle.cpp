#include "Particle.h"

Particle::Particle(Gosu::Graphics& graphics, const std::wstring& filename, Vec offset, float life, Vec acc, Vec pos, Vec vel) : Dynamic(graphics, filename, Vec(pos.x, pos.y), 16, 16, 7) {
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

void Particle::reset(Vec pos, Vec vel) {
  this->life = this->startLife;
  this->setPosition(pos);
  this->setVelocity(vel);
}

void Particle::update(float time, const Map& map) {
  this->life -= time * 10;
  int a = 255 * (this->life / this->startLife);
  this->Dynamic::update(time, map);
}
