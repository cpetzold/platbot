#include "Rope.h"

Rope::Rope(RopeNode* player, double angle, int maxLength = 30) {
  this->player = player;
  this->maxLength = maxLength;

}

Rope::~Rope() {
  // clean house!
}

void Rope::Shoot(float angle) {
  // shoot code here!
}

void Rope::Update(float t) {
  // update code here!
}

sf::Shape * GetLines() {
  return this->lines;
}

