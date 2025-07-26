#pragma once

#include "pch.h"
#include "player.h"
#include "background.h"

class game {
private:
    sf::RenderWindow* window;

    sf::Clock clock;

    void initVariables();
    void initWindow();

public:
    int frameWidth, frameHeight;
    float scale, animationSpeed;
    float playerMoveSpeed, gravity;
    float ground, frameTimer, dt;

    int playerJumping, playerInAir;
    sf::Vector2f playerVelocity;

    player* p;
    background* bg;

    game();
    virtual ~game();

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