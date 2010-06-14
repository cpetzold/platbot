#ifndef DYNAMIC_H_INCLUDED
#define DYNAMIC_H_INCLUDED

#include "Vector2D.h"
#include "Animatable.h"
#include "Map.h"

class Dynamic : public Animatable{
    private:
        float damping;
        float mass;

        Vector2D force;

        Vector2D pos;
        Vector2D vel;
        Vector2D acc;

    public:
        Dynamic(const sf::Image& img, sf::Vector2f startPos, int fw, int fh, int ef=3, float sp=1.0, int st=0, float d=2.0, float m=1.f)
        :Animatable(img, startPos, fw, fh, ef, sp, st), damping(d), mass(m){pos.x=startPos.x; pos.y=startPos.y; SetX(pos.x); SetY(pos.y);};

        Dynamic();
        //~Dynamic();

        Vector2D getPosition() const {return pos;};
        Vector2D getVelocity() const {return vel;};
        Vector2D getAcceleration() const {return acc;};

        void setPosition(Vector2D newPos){pos = newPos; SetX(pos.x); SetY(pos.y);};
        void setAcceleration(Vector2D newAcc){acc = newAcc;};
        void setVelocity(Vector2D newVel){vel = newVel;};

        void setPosition(float x, float y);
        void setAcceleration(float x, float y);
        void setVelocity(float x, float y);

        void applyForce(Vector2D force);

        void update(float time, const Map& map);

        bool mapCollideX(const Map& map);
        bool mapCollideY(const Map& map);

        void collideX(const sf::Rect<float>& overlap);
        void collideY(const sf::Rect<float>& overlap, float friction);



        sf::Rect<float> getAABB() const;

        bool onGround;

};

#endif // DYNAMIC_H_INCLUDED
