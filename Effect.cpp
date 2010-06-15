#include "Effect.h"

Effect::Effect(const sf::Image& img, Vector2D offset, int num, Vector2D pos, Vector2D posVar, Vector2D vel, Vector2D velVar, Vector2D acc, float life, bool repeat): pos(pos), posVar(posVar), vel(vel), velVar(velVar), acc(acc), repeat(repeat) {
  srand(time(NULL));
  
  cout << this->pos.x << endl;
  
  for (int i = 0; i < num; i++) {
    Particle p(img, offset, life, acc);
    this->SetParticle(p);
    this->actives.push_back(p);
    this->particles.push_back(p);
  }
  
}

Effect::Effect() {
  
}

void Effect::Play() {
  for (int i = 0; i < this->particles.size(); i++) {
    this->actives.push_back(this->particles[i]);
    this->SetParticle(this->actives[i]);
  }
}

void Effect::Update(float time, const Map& map) {

  for (int i = 0; i < this->actives.size(); i++) {
    this->actives[i].Update(time, map);
    
    if (this->actives[i].Dead()) {
      
      if (this->repeat) {
        this->SetParticle(this->actives[i]);
      } else {
        this->actives.erase(this->actives.begin()+i);
      }
    }
  }
}

void Effect::SetParticle(Particle & p) {
  Vector2D pos = this->pos.RandCenter(this->posVar);
  Vector2D vel = this->vel.RandCenter(this->velVar);
  p.Reset(pos, vel);
}

void Effect::Draw(sf::RenderWindow &window) {
  
  for (int i = 0; i < this->actives.size(); i++) {
    window.Draw(this->actives[i]);
  }
  
}




void Smoke::Update(float time, const Map& map) {
  Effect::Update(time, map);

}