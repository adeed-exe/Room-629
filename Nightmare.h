#pragma once

#include "PCH.h"

class Game;

class Nightmare {
private:
    Game* game; // Pointer to the main game instance

    // Textures for the nightmare
    sf::Texture nightmareTexture;

    float frameTimer; // Timer to control animation speed

    // Animation frame control
    int idleX, idleY, totalIdle;
    int walkX, walkY, totalWalk;
    int runX, runY, totalRun;
    int attackX, attackY, totalAttack;

    int frameWidth, frameHeight;

    void initNightmare(); // Load texture and set initial values

public:
    sf::Sprite nightmareChar; // Sprite representing the nightmare

    Nightmare(Game* gamePtr);

    // Animate functions
    void animateIdle();
    void animateWalk();
    void animateRun();
    void animateAttack();

    // Return the nightmare sprite for Game class
    sf::Sprite& getNightmare();
};