#include "ObjectManager.h"

void ObjectManager::addObject(Dynamic* addedObj){
    this->dynamics.push_back(addedObj);
}

void ObjectManager::checkCollisions(){
    Dynamic* currentObj;
    Vector2D pos;
    sf::Rect<float> overlap;

    for(vector<Dynamic*>::iterator it = this->dynamics.begin(); it < dynamics.end(); it++){
        currentObj = *it;
        pos = currentObj->getPosition();
        int x = (pos.x/this->tilesize)-1;
        int y = (pos.y/this->tilesize)-1;

        //cout << x << " " << y;

        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                try{
                    const Tile& toCheck = this->map.at(x+j, y+i);

                    if(toCheck.IsSolid()){

                        if(toCheck.getAABB().Intersects(currentObj->getAABB(), &overlap)){
                            //currentObj->handleCollision(overlap, j, i);
                        }
                    }
                }
                catch(exception e){
                    //cout << "OUT O' BOUNDSz" << endl;
                }

            }
        }
    }
}
void ObjectManager::handleCollisions(){

}

ObjectManager::~ObjectManager(){

}
