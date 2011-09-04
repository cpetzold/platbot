#include "Tile.h"

Rect Tile::getAABB() const{
    float l, t, r, b;
    float hw = this->width() / 2;  //half width
    float hh = this->height() / 2;  //half height
    l = this->pos.x - hw;
    r = this->pos.x + hw;
    t = this->pos.y - hh;
    b = this->pos.y + hh;
    return(Rect(l,t,r,b));
}