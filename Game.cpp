#include "Game.h"

Game::Game(string title, sf::VideoMode videomode, unsigned long style, int fps) {
  this->window.Create(videomode, title.c_str(), style);
  this->window.SetFramerateLimit(fps);

  this->player = new Player(*this->data.GetImage("player.png"), sf::Vector2f(0,-32), this->window.GetInput());
  this->player->SetScale(2,2);


  this->view = window.GetDefaultView();
  this->fps = fps;
}

Game::~Game() {
    delete this->player;
}

bool Game::Init() {

  this->map = Map("coolmap.map", this->data);
  //this->collisionMgr(CollisionManager(map));
  //collisionMgr.addObject(player);
  //this->player = Player(this->data.GetImage("player.png"), this->data.GetImage("player_mask.png"), sf::Vector2f(-400, -900));

  //this->sprites.push_back((sf::Sprite)this->player);


  return true;
}

void Game::Update() {
  float t = this->clock.GetElapsedTime();
  this->clock.Reset();

  this->applyGravity(1500.f);

  this->player->update(t);
  this->player->checkMapCollisions(this->map);


  this->view.SetCenter(this->player->GetPosition());
  this->window.SetView(this->view);


}

void Game::Draw() {
  this->window.Clear(sf::Color(0,0,0,255));
  //this->window.SetView(this->view);

  /*
  vector <sf::Sprite>::iterator it = this->sprites.begin();
  while (it != this->sprites.end()) {
    this->window.Draw(*it);
    ++it;
  }*/

  this->window.Draw(*this->player);

  this->map.Draw(this->window);

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
