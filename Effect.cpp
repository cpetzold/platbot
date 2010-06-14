#include "Effect.h"

Effect::Effect(const sf::Image& img, Vector2D offset, int num, Vector2D pos, Vector2D posVar, Vector2D vel, Vector2D velVar, Vector2D acc, float life): pos(pos), posVar(posVar), vel(vel), velVar(velVar), acc(acc) {
  
  cout << this->pos.x << endl;
  
  for (int i = 0; i < num; i++) {
    Particle p(img, offset, life, acc);
    this->SetParticle(p);
    this->actives.push_back(p);
  }
  
}

Effect::Effect() {
  
}

void Effect::Update(float time, const Map& map) {

  for (int i = 0; i < this->actives.size(); i++) {
    this->actives[i].Update(time, map);
    
    if (this->actives[i].Dead()) {
      this->SetParticle(this->actives[i]);
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