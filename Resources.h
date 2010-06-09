#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <memory>
#include <string>
#include <iostream>
using namespace std;

class Resources {
private:
  string dataPath;

  map <string, sf::Image*> images;
  string imagesPath;

  map <string, sf::SoundBuffer> soundBuffers;
  string soundBuffersPath;

  map <string, sf::Font> fonts;
  string fontsPath;

public:

  Resources();
  Resources(string dataPath, string imagesPath, string soundBuffersPath, string fontsPath);
  ~Resources();

  sf::Image* GetImage(string path);
  sf::Image* GetShadow(string path);
  sf::SoundBuffer& GetSoundBuffer(string path);
  sf::Font& GetFont(string path, int charSize);
  sf::Font& GetFont(string path);

};

#endif
