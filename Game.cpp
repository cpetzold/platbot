#include "Game.h"

Game::Game(string title, sf::VideoMode videomode, unsigned long style, int fps) {
  this->window.Create(videomode, title.c_str(), style);
  this->window.SetFramerateLimit(fps);
  this->view = this->window.GetDefaultView();
  this->window.SetView(this->view);
  this->fps = fps;
}

Game::~Game() {
    delete this->player;
}

bool Game::Init() {

  this->map = Map("test.map", this->data);
  this->player = new Player(*this->data.GetImage("player.png"), sf::Vector2f(16,320), this->window.GetInput());
  this->player->setShadow(*this->data.GetShadow("player.png"));

  //this->collisionMgr(CollisionManager(map));
  //collisionMgr.addObject(player);
  return true;
}

void Game::Update() {
  float t = this->clock.GetElapsedTime();
  this->clock.Reset();

  this->applyGravity(1500.f);

  this->player->update(t, this->map);
  //this->player->checkMapCollisions(this->map);


  this->view.SetCenter(this->player->GetPosition());
}

void Game::Draw() {
  this->window.Clear(sf::Color(255,255,255,255));
  //this->window.SetView(this->view);

  /*
  vector <sf::Sprite>::iterator it = this->sprites.begin();
  while (it != this->sprites.end()) {
    this->window.Draw(*it);
    ++it;
  }*/

  this->window.Draw(*this->player->getShadow());
  this->map.DrawShadows(this->window);


  this->map.Draw(this->window);

  this->window.Draw(*this->player);




  //cout << 1.f / this->window.GetFrameTime() << endl; // show fps
  this->window.Display();
}

void Game::HandleEvents() {
  while(this->window.GetEvent(this->event)) {
    switch (this->event.Type) {
      case sf::Event::Closed:
        this->window.Close();
        break;
      case sf::Event::KeyPressed:
        switch (this->event.Key.Code) {
          case sf::Key::Escape:
            this->window.Close();
            break;
          case sf::Key::Space:

            break;
          default:
            //cout << this->event.Key.Code << endl;
            break;
        }
        break;
      default:
        break;
    }
  }
}

void Game::HandleInput() {
  const sf::Input& input = this->window.GetInput();

  if (input.IsKeyDown(sf::Key::Up)) {

  }

  if (input.IsKeyDown(sf::Key::Down)) {

  }

  if (input.IsKeyDown(sf::Key::Right)) {

  }

  if (input.IsKeyDown(sf::Key::Left)) {

  }

}

void Game::Run() {
  while(this->window.IsOpened()) {
    this->HandleEvents();
    this->HandleInput();

    this->Update();
    this->Draw();
  }
}

void Game::applyGravity(float grav){
    this->player->setAcceleration(this->player->getAcceleration().x, grav);
}
