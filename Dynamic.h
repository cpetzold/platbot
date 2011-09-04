#ifndef DYNAMIC_H_INCLUDED
#define DYNAMIC_H_INCLUDED

#include <Gosu/Gosu.hpp>
#include <Gosu/TR1.hpp>

#include "Vec.h"
#include "Rect.h"
#include "Animatable.h"
#include "Map.h"

class Dynamic : public Animatable {
private:
  float damping;
  float mass;

  Vec force;
  Vec pos;
  Vec vel;
  Vec acc;
  bool grounded;

public:
  Dynamic(Gosu::Graphics& graphics, const std::wstring &filename, Vec start, int fw, int fh, int ef=3, float sp=1.0, int st=0, float d=1.0, float m=1.f) : Animatable(graphics, filename, start, fw, fh, ef, sp, st), damping(d), mass(m), pos(start) {
  };

  Vec getPosition() const {return pos;};
  Vec getVelocity() const {return vel;};
  Vec getAcceleration() const {return acc;};
  Rect getAABB() const;

  void setPosition(Vec newPos){pos = newPos;};
  void setAcceleration(Vec newAcc){acc = newAcc;};
  void setVelocity(Vec newVel){vel = newVel;};
  
  void applyForce(Vec force);

  void update(float time, const Map& map);

  bool mapCollideX(const Map& map);
  bool mapCollideY(const Map& map);

  void collideX(const Rect& overlap);
  void collideY(const Rect& overlap, float friction);
};

#endif // DYNAMIC_H_INCLUDED
