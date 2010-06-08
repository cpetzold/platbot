#include "Dynamic.h"

Dynamic::Dynamic(){

    }
Dynamic::~Dynamic(){

    }

//Set the position of the object
void Dynamic::setPosition(float x, float y){
    pos.x = x;
    pos.y = y;
}

//Set the acceleration of the object
void Dynamic::setAcceleration(float x, float y){
    acc.x = x;
    acc.y = y;
}

//Set the veleocity of the ojbect
void Dynamic::setVelocity(float x, float y){
    vel.x = x;
    vel.y = y;
}

void Dynamic::update(float time){

    vel*=damping;

    vel+=acc*time;

//    cout << (acc*time).x << endl;

    pos+=vel*time;

//    cout << "Velocity:(" << vel.x << "," << vel.y << ")";
//    cout << "Acceleration:(" << acc.x << "," << acc.y << ")";
//    cout << "Position:(" << pos.x << "," << pos.y << ")" << endl << endl;

    this->Animatable::SetX(pos.x);
    this->Animatable::SetY(pos.y);

    this->Animatable::update(time);
}

void Dynamic::checkMapCollisions(const Map& map){
    int x = pos.x/32;  //32 is current tilesize
    int y = pos.y/32;

    x--;
    y--;

    sf::Rect<float> overlap;
    //cout << x << " " << y;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            try{
                const Tile& toCheck = map.at(x+j, y+i);

                if(toCheck.IsSolid()){

                    if(toCheck.getAABB().Intersects(this->getAABB(), &overlap)){
                        handleCollision(overlap);
                    }
                }
            }
            catch(exception e){
                //cout << "OUT O' BOUNDSz" << endl;
            }

        }
    }

}

void Dynamic::handleCollision(const sf::Rect<float>& overlap){

    sf::Rect<float> currentRect = this->getAABB();

    cout << overlap.Bottom << " " <<currentRect.Bottom << endl;

    //Object coming from top, ie colliding with ground
    if(currentRect.Bottom == overlap.Bottom){
        float y = overlap.Top-16;
        cout << y << endl;

        if(overlap.GetWidth() > overlap.GetHeight())
            this->setPosition(this->getPosition().x, y);
    }
    //Object coming from bottom, ie hitting the ceiling
    else if(currentRect.Top == overlap.Top){
        float y = overlap.Bottom+16;
        cout << y << endl;

        if(overlap.GetWidth() > overlap.GetHeight())
            this->setPosition(this->getPosition().x, y);
    }

    //Object hitting a wall to the left
    if(currentRect.Left == overlap.Left){
        float x = overlap.Right+16;
        cout << x << endl;

        if(overlap.GetWidth() < overlap.GetHeight())
            this->setPosition(x, this->getPosition().y);
    }
    //Object hitting a wall to the right
    else if(currentRect.Right == overlap.Right){
        float x = overlap.Left-16;
        cout << x << endl;

        if(overlap.GetWidth() < overlap.GetHeight())
            this->setPosition(x, this->getPosition().x);
    }

    this->setVelocity(this->getVelocity().x, 0);
    this->setAcceleration(this->getAcceleration().x, 0);



}

sf::Rect<float> Dynamic::getAABB() const{
    float l, t, r, b;
    float hw = this->GetSize().x / 2;  //half width
    float hh = this->GetSize().y / 2;  //half height
    l = this->GetPosition().x-hw;
    r = this->GetPosition().x+hw;
    t = this->GetPosition().y-hh;
    b = this->GetPosition().y+hh;

    //cout << "Top: " << t << " Bottom: " << b << endl;
    //cout << "Left: " << l << " Right: " << r << endl;

    return(sf::Rect<float>(l,t,r,b));

}
