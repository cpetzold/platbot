/*
 *  Game.h
 *  ropebot
 *
 *  Created by Conner Petzold on 4/17/10.
 *
 */

#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "Resources.h"
#include "Map.h"

class Game {
private:
  sf::Event             event;        // The event
  sf::View              view;          // The view
  sf::RenderWindow      window;     // The render window
  
  Resources             data;
  vector <sf::Sprite>   sprites;
  sf::String            logo;
  Map                   map;
  
public:
  
  Game(string title);
  Game(string title, int width, int height);
  ~Game();                        // The destructor
  
  bool Init();                    // Initializes everything not in the constructor
  void HandleEvents();                // Handles input from the player
  void HandleInput();
  void Draw();                    // Draws the scene
  void Update();                    // Updates variables, game object, etc.
  void Run();
};

#endif