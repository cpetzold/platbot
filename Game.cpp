#include "Game.h"

Game::Game(string title) {
  this->window.Create(sf::VideoMode::GetDesktopMode(), title.c_str(), sf::Style::Fullscreen);
  this->window.SetFramerateLimit(0);
  this->view = window.GetDefaultView();
}

Game::Game(string title, int width, int height) {
  this->window.Create(sf::VideoMode(width, height, 32), title.c_str());
  this->window.SetFramerateLimit(0);
  this->view = window.GetDefaultView();
}

Game::~Game() {
     // Clean stuff up
}

bool Game::Init() {
  
  Map map = Map(*(this->data.GetImage("maps/test2.png")), *(this->data.GetImage("tilesets/tribal.png")));
  this->sprites.push_back(map.GetSprite());
  
  
  
  
  return true;
}

void Game::Update() {
  //Update stuff
}

void Game::Draw() {
  this->window.Clear();
  this->window.SetView(this->view);
  
  vector <sf::Sprite>::iterator it = this->sprites.begin();
  while (it != this->sprites.end()) {
    this->window.Draw(*it);
    ++it;
  }
    
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
  
  
  this->view.SetCenter(input.GetMouseX(), input.GetMouseY());
  
}

void Game::Run() {
  while(this->window.IsOpened()) {
    this->HandleEvents();
    this->HandleInput();

    this->Update();
    this->Draw();
  }
}