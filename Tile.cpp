/*
 *  Tile.cpp
 *  platbot
 *
 *  Created by Conner Petzold on 5/30/10.
 *  Copyright 2010 CSU. All rights reserved.
 *
 */

#include "Tile.h"


sf::Rect<float> Tile::getAABB() const{
    float l, t, r, b;
    float hw = this->GetSize().x/2;  //half width
    float hh = this->GetSize().y/2;  //half height
    l = this->GetPosition().x-hw;
    r = this->GetPosition().x+hw;
    t = this->GetPosition().y-hh;
    b = this->GetPosition().y+hh;

    //cout << "Top: " << t << " Bottom: " << b << endl;
    //cout << "Left: " << l << " Right: " << r << endl;

    return(sf::Rect<float>(l,t,r,b));

}
