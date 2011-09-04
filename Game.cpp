#include "Game.h"

Game::Game(wstring title, int width, int height, bool fullscreen, int fps) : Window(width, height, fullscreen) {
  this->setCaption(title);
  this->fps = fps;
  
  wstring mapFilename = Gosu::resourcePrefix() + L"test.map";
  this->map = Map(this->graphics(), mapFilename);
  //  this->player = new Player(*this->data.GetImage("player.png"), sf::Vector2f(200,200), this->window.GetInput());
}

Game::~Game() {
    delete this->player;
}

void Game::update() {
  
//  this->player->update(t, this->map);
//  this->effect->update(t, this->map);
//  this->effect->setPosition(this->player->getPosition());
//  this->player->checkMapCollisions(this->map);
//  this->view.SetCenter(sf::Vector2f(this->player->GetPosition().x, 200));
}

void Game::draw() {
  this->map.draw();
}

void Game::buttonDown(Gosu::Button b) {
  int button = b.id();
  switch (button) {
    case (Gosu::kbEscape):
      this->close();
      exit(1);
      break;
    default:
      break;
  }
}

int main() {
  Game game(L"Platbot", 1440, 900);
  game.show();
}
