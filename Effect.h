#ifndef EFFECT_H
#define EFFECT_H

#include "Particle.h"

class Effect {
public:
  Effect(Gosu::Graphics& graphics, const std::wstring& filename,  Vec offset, int num = 20, Vec pos = Vec(0,0), Vec posVar = Vec(0,0), Vec vel = Vec(0,0), Vec velVar = Vec(0,0), Vec acc = Vec(0,0), float life = 30, bool repeat = true);
  Effect();
  
  void setParticle(Particle & p);
  void setPosition(Vec pos) { this->pos = pos; };
  void play();
  
  void update(float time, const Map& map);
  void draw();
  
private:
  vector<Particle> particles;
  vector<Particle> actives;
  
  Vec pos;
  Vec vel;
  Vec posVar;
  Vec velVar;
  Vec acc;
  bool repeat;
};


class Smoke : public Effect {
public:
  Smoke(Gosu::Graphics& graphics, const std::wstring& filename, Vec offset, int num = 50, Vec pos = Vec(0,0)): Effect(graphics, filename, offset, num, pos, Vec(2,2), Vec(0,0), Vec(20,0), Vec(0, -50.f)) {};
  
  void update(float time, const Map& map);
};


#endif
