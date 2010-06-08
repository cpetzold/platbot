#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Dynamic.h"

class Player : public Dynamic{
    public:
        Player(const sf::Image& img, sf::Vector2f startPos, const sf::Input& in);
        Player();
        void update(float time);
        void handleInput();

    private:
        const sf::Input& input;
        bool direction; //1 for left, 0 for right
        bool canJump; //1 when on the ground, 0 otherwise
};
#endif // PLAYER_H_INCLUDED
