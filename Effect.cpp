#include "Effect.h"

Effect::Effect(Gosu::Graphics& graphics, const std::wstring& filename, Vec offset, int num, Vec pos, Vec posVar, Vec vel, Vec velVar, Vec acc, float life, bool repeat): pos(pos), posVar(posVar), vel(vel), velVar(velVar), acc(acc), repeat(repeat) {
  srand(time(NULL));
  
  cout << this->pos.x << endl;
  
  for (int i = 0; i < num; i++) {
    Particle p(graphics, filename, offset, life, acc);
    this->setParticle(p);
    this->actives.push_back(p);
    this->particles.push_back(p);
  }
  
}

Effect::Effect() {
  
}

void Effect::play() {
  for (int i = 0; i < this->particles.size(); i++) {
    this->actives.push_back(this->particles[i]);
    this->setParticle(this->actives[i]);
  }
}

void Effect::update(float time, const Map& map) {

  for (int i = 0; i < this->actives.size(); i++) {
    this->actives[i].update(time, map);
    
    if (this->actives[i].dead()) {
      
      if (this->repeat) {
        this->setParticle(this->actives[i]);
      } else {
        this->actives.erase(this->actives.begin()+i);
      }
    }
  }
}

void Effect::setParticle(Particle & p) {
  Vec pos = this->pos.randCenter(this->posVar);
  Vec vel = this->vel.randCenter(this->velVar);
  p.reset(pos, vel);
}

void Effect::draw() {
  
  for (int i = 0; i < this->actives.size(); i++) {
    
  }
  
}




void Smoke::update(float time, const Map& map) {
  Effect::update(time, map);

}