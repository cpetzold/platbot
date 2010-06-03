#include "Dynamic.h"

Dynamic::Dynamic(){

    }
Dynamic::~Dynamic(){

    }

//Set the position of the object
void Dynamic::setPosition(float x, float y){
    pos = Vector2D(x,y);
}

//Set the acceleration of the object
void Dynamic::setAcceleration(float x, float y){
    acc = Vector2D(x,y);
}

//Set the veleocity of the ojbect
void Dynamic::setVelocity(float x, float y){
    vel = Vector2D(x,y);
}

void Dynamic::update(float time){

    vel*=damping;

    vel+=acc*time;
    pos+=vel*time;

    this->Animatable::SetX(pos.x);
    this->Animatable::SetY(pos.y);

    this->Animatable::update(time);
}

void Dynamic::checkMapCollisions(const Map& map){
    int x = pos.x-1;
    int y = pos.y-1;

//    Tile toCheck;

//    for(int i=0; i<3; i++){
//        for(int j=0; j<3; j++){
//            toCheck = map.at(x+j, y+i);
//            if(toCheck.solid){
//                if(toCheck.GetSubRect().Intersects(Animatable::GetSubRect())){
//                    cout << "COLLISIONZ ZOMG";
//                }
//            }
//
//        }
//    }

}
