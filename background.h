#pragma once

#include "pch.h"

class Game;

class Background {
private:
    Game* game;

    sf::Texture backgroundTexture1; sf::Sprite background1;
    sf::Texture backgroundTexture2; sf::Sprite background2;
    sf::Texture backgroundTexture3; sf::Sprite background3;
    sf::Texture backgroundTexture4; sf::Sprite background4;

    void initBackground();

public:
    Background(Game* gamePtr);

    void moveLeft();
    void moveRight();
    void jump();

    sf::Sprite& getBackground1();
    sf::Sprite& getBackground2();
    sf::Sprite& getBackground3();
    sf::Sprite& getBackground4();
};