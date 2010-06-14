#include "Game.h"

int main() {

  Game game("Platbot");//, sf::VideoMode(1680,1050,32), sf::Style::Fullscreen, 50);
  game.Init();
  game.Run();

  return EXIT_SUCCESS;
}
