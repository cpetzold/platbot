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
    this->getShadow()->SetX(pos.x);
    this->getShadow()->SetY(pos.y);

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

    float offsetY = overlap.GetHeight();
    float offsetX = overlap.GetWidth();

    if(this->getPosition().y < overlap.Top){
        this->setPosition(this->getPosition().x, this->getPosition().y-offsetY);
        onGround = true;
    }
    else if(this->getPosition().y > overlap.Bottom)
        this->setPosition(this->getPosition().x, this->getPosition().y+offsetY);

    //Horizontal detection
    else if(this->getPosition().x < overlap.Right)
        this->setPosition(this->getPosition().x-offsetX, this->getPosition().y);
    else if(this->getPosition().x > overlap.Left)
        this->setPosition(this->getPosition().x+offsetX, this->getPosition().y);

    /*
    //Object coming from top, ie colliding with ground
    if(currentRect.Bottom == overlap.Bottom){
        float y = overlap.Top-16;
        //cout << "BOTTOM" << endl;

        if(currentRect.Top != overlap.Top){
            cout << "FIXED TOP" <<endl;
            this->setPosition(this->getPosition().x, y);

            this->setPosition(this->getPosition().x, y);
            this->setVelocity(this->getVelocity().x, 0);
            this->setAcceleration(this->getAcceleration().x, 0);
        }
    }
    //Object coming from bottom, ie hitting the ceiling
    else if(currentRect.Top == overlap.Top){
        float y = overlap.Bottom+16;
        //cout << "TOP" << endl;

        if(currentRect.Bottom != overlap.Bottom){
            this->setPosition(this->getPosition().x, y);

            this->setPosition(this->getPosition().x, y);
            this->setVelocity(this->getVelocity().x, 0);
            this->setAcceleration(this->getAcceleration().x, 0);
        }
    }

    //Object hitting a wall to the left
    if(currentRect.Left == overlap.Left){
        float x = overlap.Right+16;
        //cout << "LEFT: " << currentRect.Right << ", " << overlap.Right << endl;

        if(currentRect.Right != overlap.Right){
            cout << "FIXED LEFT" << endl;
            this->setPosition(x, this->getPosition().y);
            this->setVelocity(0, this->getVelocity().y);
            this->setAcceleration(x, this->getAcceleration().y);
        }
    }
    //Object hitting a wall to the right
    else if(currentRect.Right == overlap.Right){
        float x = overlap.Left-16;
        //cout << "RIGHT" << endl;

        if(currentRect.Left != overlap.Left){
            cout << "FIXED RIGHT" << endl;
            this->setPosition(x, this->getPosition().y);
            this->setVelocity(0, this->getVelocity().y);
            this->setAcceleration(x, this->getAcceleration().y);
        }
    }

    */



}

sf::Rect<float> Dynamic::getAABB() const{
    float l, t, r, b;
    /*
    float hw = (this->GetSize().x / 2);  //half width
    float hh = (this->GetSize().y / 2);  //half height
     */
    float hw = 6;
    float hh = 9;
    l = this->GetPosition().x-hw;
    r = this->GetPosition().x+hw;
    t = this->GetPosition().y-hh;
    b = this->GetPosition().y+hh;

    //cout << "Top: " << t << " Bottom: " << b << endl;
    //cout << "Left: " << l << " Right: " << r << endl;

    return(sf::Rect<float>(l,t,r,b));

}
