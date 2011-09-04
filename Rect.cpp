#include "Rect.h"

Vec Rect::bottomRight() {
  return Vec(this->right, this->bottom);
}

bool Rect::contains(float x, float y) {
  return this->contains(Vec(x, y));
}

bool Rect::contains(Vec point) {
  return (point >= this->pos) && (point <= this->bottomRight());
}

bool Rect::contains(Rect rect) {
  return this->contains(rect.pos) && this->contains(rect.bottomRight());
}

bool Rect::intersects(Rect rect) {
  return this->contains(rect.pos) || this->contains(rect.bottomRight());
}

Rect Rect::intersection(Rect rect) {
  float x0 = max(this->pos.x, rect.pos.x);
  float x1 = min(this->pos.x + this->dim.x, rect.pos.x + rect.dim.x);
  
  if (x0 <= x1) {
    float y0 = max(this->pos.y, rect.pos.y);
    float y1 = min(this->pos.y + this->dim.y, rect.pos.y + rect.dim.y);
    
    if (y0 <= y1) {
      return Rect(x0, y0, x1 - x0, y1 - y0);
    }
  }
  return NULL;
}