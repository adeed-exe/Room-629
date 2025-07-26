#pragma once

#include "pch.h"

class Game;

class Player {
private:
    Game* game;

    sf::Texture playerTexture;
    sf::Sprite playerChar;

    float frameTimer;

    int idleX, idleY, totalIdle;
    int runX, runY, totalRun;
    int jumpX, jumpY, totalJump;

    void initPlayer();

public:
    Player(Game* gamePtr);

    void animateIdle();
    void animateRun();
    void animateJump();

    sf::Sprite& getSprite();
};