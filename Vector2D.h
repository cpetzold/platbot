#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class Vector2D {  
public:
  float x; 
  float y;
  
	Vector2D(float x = 0, float y = 0);
	~Vector2D();
  
	Vector2D operator*(float scalar) const;
  void operator*=(float scalar);
  
  Vector2D operator/(float scalar) const;
  
	Vector2D operator+(const Vector2D &vect) const;
  void operator+=(const Vector2D &vect);
  
	Vector2D operator-(const Vector2D &vect) const;
  void operator-=(const Vector2D &vect);
  
  void SetXY(float x, float y);
  
  void Set(sf::Vector2<float> v);
  sf::Vector2<float> Get();
  
	void Rotate(float angle);
  
	float CrossProduct(const Vector2D &vect2) const;
  float DotProduct(const Vector2D &vect) const;
  
	float Magnitude();
	void Normalise();
  
  Vector2D RandCenter(const Vector2D &var);
};

#endif