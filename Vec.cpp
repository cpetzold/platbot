#include "Vec.h"

Vec Vec::operator*(float scalar) const {
  return Vec(this->x * scalar, this->y * scalar);
}
void Vec::operator*=(float scalar) {
  this->x *= scalar;
  this->y *= scalar;
}

Vec Vec::operator/(float scalar) const {
  return Vec(this->x / scalar, this->y / scalar);
}

Vec Vec::operator+(const Vec &v) const {
  return Vec(this->x + v.x, this->y + v.y);
}
void Vec::operator+=(const Vec &v) {
  this->x += v.x;
  this->y += v.y;
}

Vec Vec::operator-(const Vec &v) const {
  return Vec(this->x - v.x, this->y - v.y);
}
void Vec::operator-=(const Vec &v) {
  this->x -= v.x;
  this->y -= v.y;
}

bool Vec::operator<(const Vec &v) {
  return (this->x < v.x && this->y < v.y);
}
bool Vec::operator<=(const Vec &v) {
  return (this->x <= v.x && this->y <= v.y);
}
bool Vec::operator>(const Vec &v) {
  return (this->x > v.x && this->y > v.y);
}
bool Vec::operator>=(const Vec &v) {
  return (this->x >= v.x && this->y >= v.y);
}

void Vec::set(float x, float y) {
  this->x = x;
  this->y = y;
}

void Vec::rotate(float angle) {
  float xt = (this->x * cosf(angle)) - (this->y * sinf(angle));
  float yt = (this->y * cosf(angle)) + (this->x * sinf(angle));
  this->x = xt;
  this->y = yt;
}

float Vec::cross(const Vec &v) const {
  return (this->x * v.y) - (this->y * v.x);
}

float Vec::magnitude() {
  return sqrtf(this->x * this->x + this->y * this->y);
}

void Vec::normalize() {
  float mag = this->magnitude();
  this->x /= mag;
  this->y /= mag;
}

float Vec::dot(const Vec &v) const {
  return (this->x * v.x) + (this->y * v.y);
}

Vec Vec::randCenter(const Vec &v) {
  Vec result;
  if (v.x) result.x = (rand() % (int)v.x) - (v.x/2);
  if (v.y) result.y = (rand() % (int)v.y) - (v.y/2);
  return *this + result;
}