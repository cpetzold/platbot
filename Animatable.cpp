#include "Animatable.h"

using namespace std;

Animatable::Animatable(Gosu::Graphics &graphics, const std::wstring &filename, Vec pos, int fw, int fh, int ef, float sp, int st):
  Image(graphics, filename) {

  this->frameWidth = fw;
  this->frameHeight = fh;
  this->frameSpeed = sp;
  this->frameState = st;
  this->endFrame = ef;
  this->frame = 1;

}

void Animatable::update(float t){
  if (this->frameSpeed > 0) {
    
    this->frame += this->frameSpeed * t;
    
    if (this->frame >= this->endFrame + 1) {
      this->frame = 1;
    }

    int f = frame;

    //Calculate subrect left, top, right, and bottom
//    int l = (f - 1) * this->frameWidth;
//    int t = this->frameState * this->frameHeight + 1;
//    int r = f * this->frameWidth;
//    int b = (this->frameState + 1) * this->frameHeight;

    //cout << "Frame: " << frame << endl << "Speed: " << frameSpeed << endl;
  }
}
