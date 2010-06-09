#include "Animatable.h"

using namespace std;

Animatable::Animatable(const sf::Image& img, const sf::Vector2f& pos, int fw, int fh, int ef, float sp, int st) : sf::Sprite(img, pos){
    this->frameWidth = fw;
    this->frameHeight = fh;
    this->frameSpeed = sp;
    this->frameState = st;
    this->endFrame = ef;
    this->frame = 1;
    SetSubRect(sf::IntRect(0,0,fw,fh));
}

void Animatable::update(float time){
    this->frame+=time*frameSpeed;
    if(frame >= endFrame+1) frame=1;

    int f = frame;

    //Calculate subrect left, top, right, and bottom
    int l = (f-1)*frameWidth;
    int t = frameState*frameHeight+1;
    int r = f*frameWidth;
    int b = (frameState+1)*frameHeight;

    SetSubRect(sf::IntRect(l,t,r,b));


    //cout << "Frame: " << frame << endl << "Speed: " << frameSpeed << endl;
}