#pragma once

#include "pch.h"
#include "player.h"
#include "background.h"

class Game {
private:
    sf::RenderWindow* window;

    sf::Clock clock;

    Player* player;
    Background* background;

    void initVariables();
    void initWindow();

public:
    int frameWidth, frameHeight;
    float scale, animationSpeed;
    float playerMoveSpeed, gravity;
    float ground, frameTimer, deltaTime;

    int playerRunning, playerFell;
    int playerCrouching, isCrouchHeld;
    int playerJumping, playerInAir;
    sf::Vector2f playerVelocity;

    Game();
    virtual ~Game();

    const bool running() const;

    void pollEvents();
    void resetPlayer();
    void updatePlayer();
    void resetBackground();
    void updateBackground();
    void movementHandler();
    void update();
    void render();
};