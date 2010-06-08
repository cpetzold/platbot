#ifndef ObjectManager_H_INCLUDED
#define ObjectManager_H_INCLUDED

#include "Map.h"
#include "Dynamic.h"
#include "Vector2D.h"
#include <vector>

using namespace std;

class ObjectManager{
  private:
    Map& map;
    vector<Dynamic*> dynamics;

    int tilesize;

  public:
    ObjectManager(Map& m) : map(m){tilesize = map.getTileSize();};
    ObjectManager();
    void addObject(Dynamic* addedObj);

    void checkCollisions();
    void handleCollisions();

    ~ObjectManager();


};

#endif // ObjectManager_H_INCLUDED
