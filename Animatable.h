#ifndef ANIMATABLE_H_INCLUDED
#define ANIMATABLE_H_INCLUDED

#include <Gosu/Gosu.hpp>

#include "Vec.h"

//Class for animatable sprites
class Animatable: public Gosu::Image {
public:
  Animatable(Gosu::Graphics &graphics, const std::wstring &filename, Vec pos, int fw, int fh, int ef = 3, float sp = 10.0, int st = 0);

  void update(float time);

  int frameState;     //animation state; for different animations; ie idle, running, walking, etc
  float frame;        //current frame
  float frameSpeed;   //speed of animation, in frames/second
  int frameWidth;     //width/height in Pixels of each frame
  int frameHeight;
  int endFrame;       //last frame of animation
};

#endif // ANIMATABLE_H_INCLUDED
