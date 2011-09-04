#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <Gosu/Gosu.hpp>

#include "Vec.h"
#include "Dynamic.h"

class Player : public Dynamic {
public:
  Player(Gosu::Graphics &graphics, const std::wstring &filename, Vec startPos);
  Player();
  void update(float time, const Map& map);

private:
  bool direction; //1 for left, 0 for right
  bool canJump; //1 when on the ground, 0 otherwise

  float walkSpeed;
  float runSpeed;
  float jumpSpeed;
  float minJump;
  float runAccel;
  float airAccel;

};
#endif // PLAYER_H_INCLUDED
