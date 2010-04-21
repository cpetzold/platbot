#include "Player.h"

Player::Player(sf::Image & img, sf::Image & mask, sf::Vector2f pos) : sf::Sprite(img, pos) {
  this->SetCenter(img.GetWidth()/2, img.GetHeight()/2);
  this->mask = &mask;
  
  this->pos.SetXY(this->GetPosition().x, this->GetPosition().y);
  
  this->acc.y = 0.24;
  this->vel.x = 2;
  
  this->off.x = 25;
  this->off.y = 21;
  
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
    this->pos = this->prov;
    this->SetPosition(this->pos.x, this->pos.y);
  }

}

sf::IntRect Player::GetAABB(Vector2D pos) {
  return sf::IntRect(pos.x + this->off.x,
                     pos.y + this->off.y,
                     pos.x + this->off.x + this->mask->GetWidth(),
                     pos.y + this->off.y + this->mask->GetHeight());
}

bool Player::IsColliding(Map * m) {
  sf::IntRect playerAABB = this->GetAABB(this->prov);
  sf::IntRect mapAABB = m->GetAABB();
  
  if (playerAABB.Intersects(mapAABB)) {
    
    sf::Vector2f mapV;
    int x = 0;
    int y = 0;
    
    for (int i = playerAABB.Left; i < playerAABB.Right; i++) {
      for (int j = playerAABB.Top; j < playerAABB.Bottom; j++) {
        mapV = ((sf::Sprite *)m)->TransformToLocal(sf::Vector2f(i, j));
                
        //If both sprites have opaque pixels at the same point we've got a hit
        if ((((sf::Sprite *)m)->GetPixel(mapV.x, mapV.y).a != sf::Color(0,0,0,0).a) &&
            (this->mask->GetPixel(x, y).a != sf::Color(0,0,0,0).a)) {
          return true;
        }
        
        y++;
      }
      y = 0;
      x++;
    }
    return false;
  }
  return false;
}


void Player::HandleCollision() {
  cout << "OH SHIT A COLLISION!" << endl;
}