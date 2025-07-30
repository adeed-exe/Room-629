#pragma once

#include "pch.h"

class Game;

class Player {
private:
    Game* game; // Pointer to the main game instance
    sf::Texture playerTexture; // Texture containing sprite sheet

    float frameTimer; // Timer to control animation speed

    // Animation frame control
    int idleX, idleY, totalIdle;
    int walkX, walkY, totalWalk;
    int runX, runY, totalRun;
    int jumpX, jumpY, totalJump;
    int crouchX, crouchY, totalCrouch;
    int fallX, fallY, totalFall;

    void initPlayer(); // Load texture and set initial values

public:
    sf::Sprite playerChar; // Sprite representing the player

    Player(Game* gamePtr);
    
    // Animate functions
    void animateIdle();
    void animateWalk();
    void animateRun();
    void animateJump();
    void animateCrouch();
    void animateFall();

    // Return the player sprite for Game class
    sf::Sprite& getPlayer();
};