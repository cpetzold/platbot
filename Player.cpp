#include "Player.h"

Player::Player(Gosu::Graphics& graphics, const std::wstring& filename, Vec startPos) : Dynamic(graphics, filename, startPos, 32, 32) {
  setPosition(Vec(startPos.x, startPos.y));
  setVelocity(Vec(0,0));
  setAcceleration(Vec(0,0));
  this->frameSpeed = 10;
  
  this->direction = true;
  this->canJump = true;
  
  this->walkSpeed = 300;
  this->runSpeed = 500;
  this->jumpSpeed = 800;
  this->minJump = 1000;
  this->runAccel = 2000;
  this->airAccel = 400;

}

void Player::update(float time, const Map& map){
    this->Dynamic::update(time, map);
}

/*void Player::handleInput(){
    bool left = input.IsKeyDown(sf::Key::Left);
    bool right = input.IsKeyDown(sf::Key::Right);

    float accY = getAcceleration().y;
    float accX = getAcceleration().x;

    float maxSpeed = this->walkSpeed;

    float accel = this->runAccel;

    //half acceleration in the air
    if(!this->onGround) accel = this->airAccel;


    if(input.IsKeyDown(sf::Key::X))maxSpeed=this->runSpeed;
    //left+right movement stuff

    //if both are pressed, stop trying to move
    if (left && right){
        setAcceleration(0, accY);
        frameState = 0;
    } else if(left || right) {
        //Flip our sprite based on which direction we're going
        FlipX(left);
        //cout << this->getVelocity().x << endl;
        if (left) {
            frameState = 1;
            if(fabs(this->getVelocity().x) < maxSpeed)
                setAcceleration(-accel,accY);
            else
                setAcceleration(0, accY);
        }
        else if(right) {
            direction = 0;
            frameState = 1;
            if(fabs(this->getVelocity().x) < maxSpeed)
                setAcceleration(accel,accY);
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

            float jump = this->jumpSpeed * -(fabs(this->getVelocity().x) / this->runSpeed);


            //cout << "Jump height: " << jump << endl;

            if(jump < this->minJump) jump = -this->minJump;



            setVelocity(getVelocity().x, jump);
            //frameState = 2;
        }
    }
    if(input.IsKeyDown(sf::Key::C)){
        applyForce(Vec(500,0));
    }


}*/

