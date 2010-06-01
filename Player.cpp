#include "Player.h"

Player::Player() {
  
}

Player::Player(sf::Image & img, sf::Image & mask, sf::Vector2f pos) : sf::Sprite(img, pos) {
  this->mask = &mask;
  this->SetCenter(img.GetWidth()/2, img.GetHeight()/2);
  
  this->pos.SetXY(this->GetPosition().x, this->GetPosition().y);
  
  this->accd.y = 0.24;
  this->acc.y = this->accd.y;
  this->fric = 0.99;
  
  
  //this->vel.y = -30;
  //this->vel.x = 5;
  
}

Player::~Player() {
  
}

void Player::Update(float t, Map & m) {
  
  if (this->vel.Magnitude() < 32.0) {
    this->vel += this->acc*t;
  }
  
  this->prov = this->pos + this->vel*t + this->acc*(1.0/2.0)*(t*t);
  
  if (this->IsColliding(&m)) {
    this->HandleCollision();
  } else {
    //this->acc.y = this->accd.y;
    this->pos = this->prov;
    this->SetPosition(this->pos.x, this->pos.y);
  }
  
  
  this->acc.x = this->accd.x;

}

sf::IntRect Player::GetAABB(Vector2D pos) {
  return sf::IntRect(pos.x - (this->mask->GetWidth()/2),
                     pos.y - (this->mask->GetHeight()/2),
                     pos.x + (this->mask->GetWidth()/2),
                     pos.y + (this->mask->GetHeight()/2));
                    
}

void Player::ApplyForce(Vector2D f) {
  this->acc += f;
}

void Player::Jump() {
  this->vel.y = -4.46;
  this->acc.y = this->accd.y;
}

bool Player::IsColliding(Map * m) {

  return false;
}


void Player::HandleCollision() {
  int hh = this->mask->GetHeight()/2;
  int displace = this->last.y - this->prov.y;
  
  if (displace > 0) {
    this->acc.y = 0;
  } else {
    this->acc.y = this->accd.y;
    hh = -hh;
  }
  
  this->vel.y = 0;
  this->vel.x = 0;
  
  this->pos.y = this->prov.y + (displace - hh);
  this->SetPosition(this->pos.x, this->pos.y);
}







void Player::Debug(sf::RenderWindow & window) {
  int width = this->GetImage()->GetWidth();
  int height = this->GetImage()->GetHeight();
  
  sf::Shape spriteBox = sf::Shape::Rectangle(this->pos.x - width/2,
                                             this->pos.y - height/2,
                                             this->pos.x + width/2,
                                             this->pos.y + height/2,
                                             sf::Color(0, 255, 0, 100));
  window.Draw(spriteBox);
  
  
  sf::IntRect aabb = this->GetAABB(this->pos);
  sf::Shape aabbBox = sf::Shape::Rectangle(aabb.Left,
                                           aabb.Top,
                                           aabb.Right,
                                           aabb.Bottom,
                                           sf::Color(0, 0, 255, 100));
  window.Draw(aabbBox);
  
  
  sf::IntRect proaabb = this->GetAABB(this->prov);
  sf::Shape proaabbBox = sf::Shape::Rectangle(proaabb.Left,
                                           proaabb.Top,
                                           proaabb.Right,
                                           proaabb.Bottom,
                                           sf::Color(20, 100, 100, 100));
  window.Draw(proaabbBox);
  
  sf::Shape lastPoint = sf::Shape::Circle(this->last.x, this->last.y, 1, sf::Color(0,255,255,150));
  window.Draw(lastPoint);

}









