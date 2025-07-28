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
    int walkX, walkY, totalWalk;
    int runX, runY, totalRun;
    int jumpX, jumpY, totalJump;
    int crouchX, crouchY, totalCrouch;
    int fallX, fallY, totalFall;

    void initPlayer();

public:
    Player(Game* gamePtr);

    void animateIdle();
    void animateWalk();
    void animateRun();
    void animateJump();
    void animateCrouch();
    void animateFall();

    sf::Sprite& getSprite();
};