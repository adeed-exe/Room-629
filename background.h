#pragma once

#include "pch.h"

class game;

class background {
private:
    game* g;

    sf::Texture bg1Texture; sf::Sprite bg1;
    sf::Texture bg2Texture; sf::Sprite bg2;
    sf::Texture bg3Texture; sf::Sprite bg3;
    sf::Texture bg4Texture; sf::Sprite bg4;

    void initBackground();

public:
    background(game* gamePtr);

    void moveLeft();
    void moveRight();
    void jump();

    sf::Sprite& getBg1();
    sf::Sprite& getBg2();
    sf::Sprite& getBg3();
    sf::Sprite& getBg4();
};