#ifndef PARTICLE_H
#define PARTICLE_H

#include <Gosu/Gosu.hpp>

#include "Dynamic.h"

class Particle : public Dynamic {
public:
  Particle(Gosu::Graphics& graphics, const std::wstring& filename, Vec offset, float life = 100, Vec acc = Vec(0,0), Vec pos = Vec(0,0), Vec vel = Vec(0,0));
  Particle();
  void update(float time, const Map& map);
  bool dead() { return this->life <= 0; };
  
  void reset(Vec pos, Vec vel);
  
private:
  float startLife;
  float life;
  
};
#endif
