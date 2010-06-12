#include "Player.h"

/*-----------------------------------------
Constructor class for Player
Arguments:
    img = Image (with animations)
    startPos = start position of the player
-----------------------------------------*/

Player::Player(const sf::Image& img, sf::Vector2f startPos, const sf::Input& in) : Dynamic(img, startPos, 32, 32), input(in), canJump(1){
    setPosition(Vector2D(startPos.x, startPos.y));
    setVelocity(Vector2D(0,0));
    setAcceleration(Vector2D(0,0));
    frameSpeed = 10;
    this->direction = 1;

    this->walkSpeed = 300;
    this->runSpeed = 500;
    this->jumpSpeed = -600;
    this->runAccel = 800;

}

/*-----------------------------------------
Update method for player
Calls the parent class' update method to animate
time is usually given by a Clock variable, giving us the time in seconds since the last update

TODO:  Make a "dynamic" class
-----------------------------------------*/
void Player::update(float time, const Map& map){
    this->Dynamic::update(time, map);
    //cout << this->getVelocity().x << ", " <<this->getVelocity().y << endl;
    //cout << this->frameSpeed;
    //this->FlipX(!direction);

    handleInput();

}

/*-----------------------------------------
Handles key events
TODO: handle custom keys... maybe make a std::map to hande?
-----------------------------------------*/
void Player::handleInput(){
    bool left = input.IsKeyDown(sf::Key::Left);
    bool right = input.IsKeyDown(sf::Key::Right);

    float accY = getAcceleration().y;
    float accX = getAcceleration().x;

    float maxSpeed = this->walkSpeed;

    if(input.IsKeyDown(sf::Key::X))maxSpeed=this->runSpeed;
    //left+right movement stuff

    //if both are pressed, stop trying to move
    if (left && right){
        setAcceleration(0, accY);
        frameState = 0;
    } else if(left || right) {
        //Flip our sprite based on which direction we're going
        FlipX(left);

        if (left) {
            frameState = 1;
            if(fabs(this->getVelocity().x) < maxSpeed)
                setAcceleration(-runAccel,accY);
            else
                setAcceleration(0, accY);
        }
        else if(right) {
            direction = 0;
            frameState = 1;
            if(fabs(this->getVelocity().x) < maxSpeed)
                setAcceleration(runAccel,accY);
            else
                setAcceleration(0, accY);
        }

    } else {
        setAcceleration(0,accY);
        frameState = 0;
    }

    //jump!
    if(input.IsKeyDown(sf::Key::Space)){
        if(onGround){
            onGround = 0;
            setVelocity(getVelocity().x, jumpSpeed);
            //frameState = 2;
        }
    }
    if(input.IsKeyDown(sf::Key::C)){
        applyForce(Vector2D(500,0));
    }


}

