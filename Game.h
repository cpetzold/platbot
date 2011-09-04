#ifndef GAME_H
#define GAME_H

#include <Gosu/Gosu.hpp>
#include <Gosu/TR1.hpp>

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "Player.h"
#include "Effect.h"
#include "Map.h"


class Game : public Gosu::Window {
private:
  int fps;

  Player* player;
  Effect* effect;
  Map map;

public:

  Game(wstring title, int width, int height, bool fullscreen = false, int fps = 50);
  ~Game();

  void draw();
  void update();
  void buttonDown(Gosu::Button b);
  
  void applyGravity(float grav);
};

#endif