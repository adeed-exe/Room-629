#pragma once

#include "pch.h"

class Game;

class Player {
private:
    Game* game; // Pointer to the main game instance

    //textures for the player
    sf::Texture playerTexture;
    sf::Texture idleTexture;
    sf::Texture walkTexture;
    sf::Texture runTexture;
    sf::Texture jumpTexture;

    float frameTimer; // Timer to control animation speed

    // Animation frame control
    int idleX, totalIdle;
    int walkX, totalWalk;
    int runX, totalRun;
    int jumpX, totalJump;

    void initPlayer(); // Load texture and set initial values

public:
    sf::Sprite playerChar; // Sprite representing the player

    Player(Game* gamePtr);
    
    // Animate functions
    void animateIdle();
    void animateWalk();
    void animateRun();
    void animateJump();

    // Return the player sprite for Game class
    sf::Sprite& getPlayer();
};