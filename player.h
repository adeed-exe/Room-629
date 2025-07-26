#pragma once

#include "pch.h"

class game;

class player {
private:
    game* g;

    sf::Texture playerTexture;
    sf::Sprite playerChar;

    float frameTimer;

    int idleX, idleY, totalIdle;
    int runX, runY, totalRun;
    int jumpX, jumpY, totalJump;

    void initPlayer();

public:
    player(game* gamePtr);

    void animateIdle();
    void animateRun();
    void animateJump();

    sf::Sprite& getSprite();
};