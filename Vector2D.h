#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class Vector2D {  
public:
  float x; 
  float y;
  
	Vector2D(float X = 0, float Y = 0);
	~Vector2D() {};
  
	Vector2D operator*(float scalar) const;
  
	Vector2D operator+(const Vector2D &vect) const;
  
	Vector2D operator-(const Vector2D &vect) const;
  
	void Rotate(float angle);
  
	float CrossProduct(const Vector2D &vect2) const;
  float DotProduct(const Vector2D &vect) const;
  
	float Magnitude();
	void Normalise();
};

#endif