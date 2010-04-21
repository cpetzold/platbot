#include "Player.h"

Player::Player(sf::Image & img, sf::Image & mask, sf::Vector2f pos) : sf::Sprite(img, pos) {
  this->SetCenter(img.GetWidth()/2, img.GetHeight()/2);
  this->mask = &mask;
  
  this->pos.SetXY(this->GetPosition().x, this->GetPosition().y);
  
  this->acc.y = 0.24;
  
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
  this->pos = this->prov;
  
  
  if (this->IsColliding(&m)) {
    this->HandleCollision();
  } else {
    this->SetPosition(this->pos.x, this->pos.y);
  }

}

sf::IntRect Player::GetAABB() {
  return sf::IntRect(this->pos.x + this->off.x,
                     this->pos.y + this->off.y,
                     this->pos.x + this->off.x + this->mask->GetWidth(),
                     this->pos.y + this->off.y + this->mask->GetHeight());
}

bool Player::IsColliding(Map * m) {
  sf::IntRect playerAABB = this->GetAABB();
  sf::IntRect mapAABB = m->GetAABB();
  
  sf::IntRect Intersection;
  
  if (playerAABB.Intersects(mapAABB, &Intersection)) {

    sf::Vector2f playerV;
    sf::IntRect playerR(0, 0, this->mask->GetWidth()-1, this->mask->GetHeight()-1);
    sf::Vector2f mapV;
    sf::IntRect mapR = ((sf::Sprite *)m)->GetSubRect();
    
    const sf::Image* img = this->GetImage();
    int width = img->GetWidth();
    int height = img->GetHeight();
    
    
    //Loop through our pixels
    for (int i = Intersection.Left; i < Intersection.Right; i++) {
      for (int j = Intersection.Top; j < Intersection.Bottom; j++) {
        
        playerV = this->TransformToLocal(sf::Vector2f(i, j));
        mapV = ((sf::Sprite *)m)->TransformToLocal(sf::Vector2f(i, j));
        
        playerV.x -= (this->off.x*2 + playerR.Right);
        playerV.y -= (this->off.y*2 + playerR.Bottom);
                
        if ((mapR.Contains(mapV.x, mapV.y)) && (playerR.Contains(playerV.x, playerV.y))) {
        
          //If both sprites have opaque pixels at the same point we've got a hit
          if ((((sf::Sprite *)m)->GetPixel(mapV.x, mapV.y).a != sf::Color(0,0,0,0).a) &&
              (this->mask->GetPixel(playerV.x, playerV.y).a != sf::Color(0,0,0,0).a)) {
            return true;
          }
        }
      }
    }
    return false;
  }
  return false;
}


void Player::HandleCollision() {
  //cout << "OH SHIT A COLLISION!" << endl;
}