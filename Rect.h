#ifndef RECT_H
#define RECT_H

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

#include "Vec.h"

class Rect {  
public:
  Vec pos; 
  Vec dim;
  
  float top;
  float bottom;
  float right;
  float left;
  
	Rect(float x = 0, float y = 0, float w = 0, float h = 0): pos(x, y), dim(w, h) {
    this->top = y;
    this->bottom = y + h;
    this->left = x;
    this->right = x + w;
  };
	Rect(Vec pos, Vec dim): pos(pos), dim(dim) {
    this->top = pos.y;
    this->bottom = pos.y + dim.y;
    this->left = pos.x;
    this->right = pos.x + dim.x;
  };
  
  Vec bottomRight();
  
  bool contains(float x = 0, float y = 0);
  bool contains(Vec point);
  bool contains(Rect rect);
  
  bool intersects(Rect rect);
  Rect intersection(Rect rect);
  
};

#endif