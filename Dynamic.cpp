#include "Dynamic.h"

Dynamic::Dynamic(){

    }
Dynamic::~Dynamic(){

    }

//Set the position of the object
void Dynamic::setPosition(float x, float y){
    pos.x = x;
    pos.y = y;
    SetX(pos.x);
    SetY(pos.y);
    this->getShadow()->SetX(pos.x);
    this->getShadow()->SetY(pos.y);
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

void Dynamic::update(float time, const Map& map){

    vel-= vel*damping * time;

    vel+=acc*time;

    Vector2D oldPos = pos;

    pos.y+=vel.y*time;
    mapCollideY(map);

    pos.x+=vel.x*time;
    mapCollideX(map);


//    cout << "Velocity:(" << vel.x << "," << vel.y << ")";
//    cout << "Acceleration:(" << acc.x << "," << acc.y << ")";
//    cout << "Position:(" << pos.x << "," << pos.y << ")" << endl << endl;

    this->Animatable::SetX(pos.x);
    this->Animatable::SetY(pos.y);
    this->getShadow()->SetX(pos.x);
    this->getShadow()->SetY(pos.y);

    this->Animatable::update(time);
}

void Dynamic::mapCollideX(const Map& map){
    int xPos = pos.x/32+.5;  //32 is current tilesize
    int yPos = pos.y/32+.5;

    //cout << xPos << " " << yPos << endl;

    sf::Rect<float> overlap;

    int x = (this->getVelocity().x>0 ? 1 : -1);
        for(int i=-1; i<3; i++){
            try{
                //checks the 3 tiles to the right or left, dependingo n velocity

                //cout<< "Checking tile at (" << xPos+x << "," << yPos+i << ")" << endl;

                const Tile& toCheck = (i==2) ? map.at(xPos,yPos) : map.at(xPos+x, yPos+i);

                if(toCheck.IsSolid()){
                    if(toCheck.getAABB().Intersects(this->getAABB(), &overlap)){
                        collideX(overlap);
                        //cout << "X Tile collision at: " << " :" << xPos+x << " " << yPos+i << endl;
                    }

                }
            }
            catch(exception e){
                //cout << "OUT O' BOUNDSz" << endl;
            }
        }
}

void Dynamic::mapCollideY(const Map& map){
    int xPos = pos.x/32+.5;  //32 is current tilesize
    int yPos = pos.y/32+.5;

    //cout << x << " " << y;

    sf::Rect<float> overlap;

    int y = (this->getVelocity().y>0 ? 1 : -1);


    for(int i=-1; i<3; i++){
        try{

            //checks the 3 tiles to the right or left, depending on velocity, and finally also check the current tile the player is on
            const Tile& toCheck = (i==2) ? map.at(xPos,yPos) : map.at(xPos+i, yPos+y);

            if(toCheck.IsSolid()){
                if(toCheck.getAABB().Intersects(this->getAABB(), &overlap)){
                    collideY(overlap);
                }
            }
        }
        catch(exception e){
            //cout << "OUT O' BOUNDSz" << endl;
        }
    }

}

void Dynamic::collideX(const sf::Rect<float>& overlap){

    float offset = (this->getPosition().x < overlap.Right) ? -overlap.GetWidth() : overlap.GetWidth();
    if(offset > 0)cout << offset << endl;
    float fixedX = this->getPosition().x + offset;

    this->setPosition(fixedX, this->getPosition().y);
    this->setVelocity(0,this->getVelocity().y);

}

void Dynamic::collideY(const sf::Rect<float>& overlap){


    float offset = (this->getVelocity().y > 0) ? -overlap.GetHeight() : overlap.GetHeight();

    if(offset < 0){
        onGround = 1;
    }

    float fixedY = this->getPosition().y + offset;

    this->setPosition(this->getPosition().x, fixedY);
    this->setVelocity(this->getVelocity().x, 0);

}

sf::Rect<float> Dynamic::getAABB() const{
    float l, t, r, b;
    //float hw = this->GetSize().x / 2;  //half width
    //float hh = this->GetSize().y / 2;  //half height
    float hw = 7.f;
    float hh = 10.f;
    l = this->getPosition().x-hw;
    r = this->getPosition().x+hw;
    t = this->getPosition().y-hh;
    b = this->getPosition().y+hh;

    //cout << "Top: " << t << " Bottom: " << b << endl;
    //cout << "Left: " << l << " Right: " << r << endl;

    return(sf::Rect<float>(l,t,r,b));

}
