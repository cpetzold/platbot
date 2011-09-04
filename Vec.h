#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class Vec {  
public:
  float x; 
  float y;
  
	Vec(float x = 0, float y = 0): x(x), y(y) {};
	~Vec() {};
  
	Vec operator*(float scalar) const;
  void operator*=(float scalar);
  
  Vec operator/(float scalar) const;
  
	Vec operator+(const Vec &v) const;
  void operator+=(const Vec &v);
  
	Vec operator-(const Vec &v) const;
  void operator-=(const Vec &v);
  
  bool operator<(const Vec &v);
  bool operator<=(const Vec &v);
  bool operator>(const Vec &v);
  bool operator>=(const Vec &v);
  
  void set(float x, float y);
  
	void rotate(float angle);
  
	float cross(const Vec &v) const;
  float dot(const Vec &v) const;
  
	float magnitude();
	void normalize();
  
  Vec randCenter(const Vec &v);
};

#endif