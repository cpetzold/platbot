#include "Resources.h"

Resources::Resources() {
  this->dataPath = "data/";
  this->imagesPath = "images/";
  this->soundBuffersPath = "sounds/";
  this->fontsPath = "fonts/";
}

Resources::Resources(string dataPath, string imagesPath, string soundBuffersPath, string fontsPath) {
  this->dataPath = dataPath;
  this->imagesPath = imagesPath;
  this->soundBuffersPath = soundBuffersPath;
  this->fontsPath = fontsPath;
}

Resources::~Resources() {
    //for(map<string, sf::Image*>::iterator it = images.begin(); it<images.end(); it++)
        //delete *it;
}

sf::Image* Resources::GetImage(string path) {
  path = this->dataPath + this->imagesPath + path;
  map <string, sf::Image*>::iterator it = this->images.find(path);
  if (it == this->images.end()) {
    this->images[path] = new sf::Image();
    (*this->images[path]).LoadFromFile(path.c_str());
    (*this->images[path]).SetSmooth(false);
  }
  return this->images[path];
}

sf::Image* Resources::GetShadow(string path) {
  string searchPath = this->dataPath + this->imagesPath + path;
  map <string, sf::Image*>::iterator it = this->images.find("s"+searchPath);
  
  if (it == this->images.end()) {
    int shadSize = 2;
    sf::Image* ref = this->GetImage(path);
    this->images["s"+searchPath] = new sf::Image(ref->GetWidth(), ref->GetHeight(), sf::Color(0,0,0,0));
    sf::Color b(0,0,0);
      
    for (int x = 0; x < this->images["s"+searchPath]->GetWidth(); x++) {
      for (int y = 0; y < this->images["s"+searchPath]->GetHeight(); y++) {
        if (ref->GetPixel(x, y).a > 0) {
          for (int i = -shadSize; i <= shadSize; i++) {
            for (int j = -shadSize; j <= shadSize; j++) {
              if (x+i > 0 && x+i < this->images["s"+searchPath]->GetWidth() && y+j > 0 && y+j < this->images["s"+searchPath]->GetHeight())
                this->images["s"+searchPath]->SetPixel(x+i, y+j, b);
            }
          }
        }
      }
    }
    
    this->images["s"+searchPath]->SetSmooth(false);
  }
    
  return this->images["s"+searchPath];
}

sf::SoundBuffer& Resources::GetSoundBuffer(string path) {
  path = this->dataPath + this->soundBuffersPath + path;
  map <string, sf::SoundBuffer>::iterator it = this->soundBuffers.find(path);
  if (it == this->soundBuffers.end()) {
    this->soundBuffers[path] = sf::SoundBuffer();
    this->soundBuffers[path].LoadFromFile(path.c_str());
  }
  return this->soundBuffers[path];
}

sf::Font& Resources::GetFont(string path, int charSize) {
  path = this->dataPath + this->fontsPath + path;
  map <string, sf::Font>::iterator it = this->fonts.find(path);
  if (it == this->fonts.end()) {
    this->fonts[path] = sf::Font();
    this->fonts[path].LoadFromFile(path.c_str(), charSize);
  }
  return this->fonts[path];
}

sf::Font& Resources::GetFont(string path) {
  return this->GetFont(path, 60);
}
