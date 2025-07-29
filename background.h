#pragma once

#include "pch.h"

class Game;

class Background {
private:
    Game* game; // Pointer to the main game instance

    // Textures containing each parallax layers of the background
    sf::Texture backgroundTexture1;
    sf::Texture backgroundTexture2;
    sf::Texture backgroundTexture3;
    sf::Texture backgroundTexture4;

    void initBackground(); // Load texture and set initial values

public:
    // Sprites representing each parallax layers of the background
    sf::Sprite background1;
    sf::Sprite background2;
    sf::Sprite background3;
    sf::Sprite background4;

    Background(Game* gamePtr);

    void moveLeft();
    void moveRight();
    void jump();

    // Return the background sprites for Game class
    sf::Sprite& getBackground1();
    sf::Sprite& getBackground2();
    sf::Sprite& getBackground3();
    sf::Sprite& getBackground4();
};