#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "Resources.h"
#include "Player.h"
#include "Map.h"

class Game {
private:
  sf::Clock             clock;
  sf::Event             event;
  sf::View              view;
  sf::RenderWindow      window;
  int                   fps;
  
  vector <sf::Sprite *> sprites;
  Resources             data;
  Player *              player;
  Map *                 map;
  
public:
  
  Game(string title, sf::VideoMode videomode = sf::VideoMode(800,600,32), unsigned long style = sf::Style::Close, int fps = 50);
  ~Game();
  
  bool Init();
  void HandleEvents();
  void HandleInput();
  void Draw();
  void Update();
  void Run();
};

#endif