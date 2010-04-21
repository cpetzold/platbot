#include "Game.h"

int main() {
  
  Game game("Ropebot");
  //Game game("Ropebot", 800, 600);
  game.Init();
  game.Run();
  
  return EXIT_SUCCESS;
}