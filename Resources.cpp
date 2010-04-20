/*
 *  Resources.cpp
 *  ropebot
 *
 *  Created by Conner Petzold on 4/17/10.
 *  Copyright 2010 CSU. All rights reserved.
 *
 */

#include "Resources.h"
#include <iostream>
using namespace std;

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

}

sf::Image* Resources::GetImage(string path) {
  path = this->dataPath + this->imagesPath + path;
  
  char cpath[1024];
  getcwd(cpath, sizeof(cpath));
  
  cout << cpath << endl;
  
  map <string, sf::Image*>::iterator it = this->images.find(path);
  if (it == this->images.end()) {
    this->images[path] = new sf::Image();
    this->images[path]->LoadFromFile(path.c_str());
  }
  return this->images[path];
}

sf::SoundBuffer* Resources::GetSoundBuffer(string path) {
  path = this->dataPath + this->soundBuffersPath + path;
  map <string, sf::SoundBuffer*>::iterator it = this->soundBuffers.find(path);
  if (it == this->soundBuffers.end()) {
    this->soundBuffers[path] = new sf::SoundBuffer();
    this->soundBuffers[path]->LoadFromFile(path.c_str());
  }
  return this->soundBuffers[path];
}

sf::Font* Resources::GetFont(string path, int charSize) {
  path = this->dataPath + this->fontsPath + path;
  map <string, sf::Font*>::iterator it = this->fonts.find(path);
  if (it == this->fonts.end()) {
    this->fonts[path] = new sf::Font();
    this->fonts[path]->LoadFromFile(path.c_str(), charSize);
  }
  return this->fonts[path];
}

sf::Font* Resources::GetFont(string path) {
  return this->GetFont(path, 60);
}