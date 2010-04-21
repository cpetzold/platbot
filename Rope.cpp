#include "Rope.h"

Rope::Rope(Player * player, int maxLength) {
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

sf::Shape * Rope::GetLines() {
  return this->lines;
}

