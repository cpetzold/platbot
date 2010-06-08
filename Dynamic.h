#ifndef DYNAMIC_H_INCLUDED
#define DYNAMIC_H_INCLUDED

#include "Vector2D.h"
#include "Animatable.h"
#include "Map.h"

class Dynamic : public Animatable{
    private:
        float mass;
        float damping;

        Vector2D force;

        Vector2D pos;
        Vector2D vel;
        Vector2D acc;

    public:
        Dynamic(const sf::Image& img, sf::Vector2f startPos, int fw, int fh, int ef=3, float sp=1.0, int st=0, float d=0.9, float m=1.f)
        :Animatable(img, startPos, fw, fh, ef, sp, st), damping(d), mass(m){pos.x=startPos.x; pos.y=startPos.y;};

        Dynamic();
        ~Dynamic();

        Vector2D getPosition(){return pos;};
        Vector2D getVelocity(){return vel;};
        Vector2D getAcceleration(){return acc;};

        void setPosition(Vector2D newPos){pos = newPos;};
        void setAcceleration(Vector2D newAcc){acc = newAcc;};
        void setVelocity(Vector2D newVel){vel = newVel;};

        void setPosition(float x, float y);
        void setAcceleration(float x, float y);
        void setVelocity(float x, float y);

        void update(float time);

        void checkMapCollisions(const Map& map);
        void handleCollision(const sf::Rect<float>& overlap);

        sf::Rect<float> getAABB() const;


};

#endif // DYNAMIC_H_INCLUDED
