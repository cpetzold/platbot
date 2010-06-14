#include "Vector2D.h"

Vector2D::Vector2D(float x, float y) {
  this->x = x;
  this->y = y;
}

Vector2D::~Vector2D() {
  // clean up shop!
}

Vector2D Vector2D::operator*(float scalar) const {
  return Vector2D(this->x * scalar, this->y * scalar);
}
void Vector2D::operator*=(float scalar) {
  this->x *= scalar;
  this->y *= scalar;
}

Vector2D Vector2D::operator/(float scalar) const {
  return Vector2D(this->x / scalar, this->y / scalar);
}

Vector2D Vector2D::operator+(const Vector2D &vect) const {
  return Vector2D(this->x + vect.x, this->y + vect.y);
}
void Vector2D::operator+=(const Vector2D &vect) {
  this->x += vect.x;
  this->y += vect.y;
}

Vector2D Vector2D::operator-(const Vector2D &vect) const {
  return Vector2D(this->x - vect.x, this->y - vect.y);
}
void Vector2D::operator-=(const Vector2D &vect) {
  this->x -= vect.x;
  this->y -= vect.y;
}

void Vector2D::SetXY(float x, float y) {
  this->x = x;
  this->y = y;
}

void Vector2D::Set(sf::Vector2<float> v) {
  this->x = v.x;
  this->y = v.y;
}
sf::Vector2<float> Vector2D::Get() {
  return sf::Vector2<float>(this->x, this->y);
}

void Vector2D::Rotate(float angle) {
  float xt = (this->x * cosf(angle)) - (this->y * sinf(angle));
  float yt = (this->y * cosf(angle)) + (this->x * sinf(angle));
  this->x = xt;
  this->y = yt;
}

float Vector2D::CrossProduct(const Vector2D &vect2) const {
  return (this->x * vect2.y) - (this->y * vect2.x);
}

float Vector2D::Magnitude() {
  return sqrtf(this->x * this->x + this->y * this->y);
}

void Vector2D::Normalise() {
  float mag = this->Magnitude();
  this->x /= mag;
  this->y /= mag;
}

float Vector2D::DotProduct(const Vector2D &vect) const {
  return (this->x * vect.x) + (this->y * vect.y);
}

Vector2D Vector2D::RandCenter(const Vector2D &var) {
  Vector2D result;
  if (var.x) result.x = (rand() % (int)var.x) - (var.x/2);
  if (var.y) result.y = (rand() % (int)var.y) - (var.y/2);
  return *this + result;
}