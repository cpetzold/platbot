#include "Game.h"

Game::Game(string title, sf::VideoMode videomode, unsigned long style, int fps) {
  this->window.Create(videomode, title.c_str(), style);
  this->window.SetFramerateLimit(fps);
  this->view = window.GetDefaultView();
  this->fps = fps;
}

Game::~Game() {
     // Clean stuff up
}

bool Game::Init() {
  
  this->map = new Map(*(this->data.GetImage("maps/test1.png")), *(this->data.GetImage("tilesets/tribal.png")));
  this->player = new Player(*(this->data.GetImage("player.png")), *(this->data.GetImage("player_mask.png")));
  
  this->sprites.push_back((sf::Sprite*)this->map);
  this->sprites.push_back((sf::Sprite*)this->player);
  
  
  return true;
}

void Game::Update() {
  float t = this->clock.GetElapsedTime() * 50;
  this->clock.Reset();
  
  this->player->Update(t, *this->map);
  this->view.SetCenter(((sf::Drawable *)this->player)->GetPosition());
}

void Game::Draw() {
  this->window.Clear();
  this->window.SetView(this->view);
  
  vector <sf::Sprite *>::iterator it = this->sprites.begin();
  while (it != this->sprites.end()) {
    this->window.Draw(**it);
    ++it;
  }

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
            cout << "space" << endl;
          default:
            cout << this->event.Key.Code << endl;
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
    cout << "up" << endl;
  }
  
  if (input.IsKeyDown(sf::Key::Down)) {
    cout << "down" << endl;
  }
  
  if (input.IsKeyDown(sf::Key::Right)) {
    cout << "right" << endl;
  }
  
  if (input.IsKeyDown(sf::Key::Left)) {
    cout << "left" << endl;
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