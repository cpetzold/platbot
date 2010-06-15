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

  cout << "GAME INITIALIZED" << endl;
  this->map = Map("Mario.map", this->data);
  this->player = new Player(*this->data.GetImage("player.png"), sf::Vector2f(200,200), this->window.GetInput());
  
  this->effect = new Effect(*this->data.GetImage("particles.png"), Vector2D(0, 0), 20, Vector2D(200,200), Vector2D(2,0), Vector2D(0,0), Vector2D(100,100), Vector2D(0, 0), 5, false);
  
  //this->view.SetCenter(sf::Vector2f(-1000,200));
  
  //this->collisionMgr(CollisionManager(map));
  //collisionMgr.addObject(player);
  return true;
}

void Game::Update() {
  float t = this->clock.GetElapsedTime();
  this->clock.Reset();

  this->applyGravity(1500.f);

  this->player->update(t, this->map);
  this->effect->Update(t, this->map);
  this->effect->SetPosition(this->player->getPosition());
  //this->player->checkMapCollisions(this->map);


  this->view.SetCenter(sf::Vector2f(this->player->GetPosition().x, 200));
}

void Game::Draw() {
  this->window.Clear(sf::Color(34,34,34,255));

  this->map.Draw(this->window);
  this->window.Draw(*this->player);
  this->effect->Draw(this->window);

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

  if (input.IsKeyDown(sf::Key::Space) && this->player->onGround) {
      this->effect->Play();
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
