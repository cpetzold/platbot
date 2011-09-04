#include "Dynamic.h"

Rect Dynamic::getAABB() const {
  float l, t, r, b;

  float hw = 0.5f;
  float hh = 0.5f;
  
  l = this->pos.x - hw;
  r = this->pos.x + hw;
  t = this->pos.y - hh;
  b = this->pos.y + hh;
  
  return(Rect(l,t,r,b));
}

void Dynamic::update(float time, const Map& map) {
  
  this->vel -= this->vel * this->damping * time;
  
  this->pos.y += this->vel.y * time;
  this->grounded = this->mapCollideY(map);

  this->pos.x += this->vel.x * time;
  this->mapCollideX(map);

  this->vel += this->acc * time;

  this->Animatable::update(time);
  
}

bool Dynamic::mapCollideX(const Map& map) {
  int xPos = this->pos.x / map.getTilesize() + .5;  //32 is current tilesize
  int yPos = this->pos.y / map.getTilesize() + .5;

  int x = (this->vel.x > 0 ? 1 : -1);
  
  for(int i = -1; i < 3; i++) {
    const Tile& toCheck = (i == 2) ? map.at(xPos, yPos) : map.at(xPos+x, yPos+i);

    if (toCheck.isSolid()) {
      if (toCheck.getAABB().intersects(this->getAABB())){
        collideX(toCheck.getAABB());
        return true;
      }
    }
  }
  return false;
}

bool Dynamic::mapCollideY(const Map& map) {
  int xPos = pos.x/ map.getTilesize() + .5;
  int yPos = pos.y/ map.getTilesize() +.5;

  int y = (this->vel.y > 0 ? 1 : -1);

  for(int i = -1; i < 3; i++){
    //checks the 3 tiles to the right or left, depending on velocity, and finally also check the current tile the player is on
    const Tile& toCheck = (i==2) ? map.at(xPos,yPos) : map.at(xPos+i, yPos+y);

    if (toCheck.isSolid()) {
      if (toCheck.getAABB().intersects(this->getAABB())) {
        collideY(toCheck.getAABB(), toCheck.getFriction());
        return true;
      }
    }
  }
  return false;

}

void Dynamic::applyForce(Vec force){
  this->acc += force / this->mass;
}

void Dynamic::collideX(const Rect& tileAABB){
  Rect currentRect = this->getAABB();
    
  float offset = (this->vel.x > 0) ?  tileAABB.left - currentRect.right : tileAABB.right - currentRect.left;

  this->pos.x += offset;
  this->vel.x = 0;
}

void Dynamic::collideY(const Rect& tileAABB, float friction){

  Rect currentRect = this->getAABB();

  float offset = (this->vel.y > 0) ? -(currentRect.bottom - tileAABB.top) : tileAABB.bottom - currentRect.top;

//  if the offset is less than 0, that means we landed on the ground
  if(offset < 0){
//    cout << "FORCE OF FRICTION: " << -100*friction*this->getVelocity().x << endl;

//    float force = -15*friction;

//    this->applyForce(Vec(force*this->getVelocity().x, 0));
    this->grounded = true;
  }

  this->pos.y += offset;
  this->vel.y = 0;

}


