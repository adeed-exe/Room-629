#pragma once

#include "pch.h"
#include "player.h"
#include "background.h"

class Game {
private:
    void initVariables(); // Initialize member variables
    void initWindow(); // Create window with settings

public:
    Game(); // Constructor
    ~Game(); // Destructor

    sf::RenderWindow* window; // Pointer to game window

    float deltaTime; // Time between frames
    sf::Clock dtClock; // Clock to measure deltaTime

    // Player/Background instances
    Player* player;
    Background* background;
    std::vector<sf::Sprite> backgrounds;

    // Constants used across game
    float scale;
    float animationSpeed;
    int frameWidth, frameHeight;

    float playerMoveSpeed;
    float gravity;
    float ground;

    // Player states
    sf::Vector2f playerVelocity;
    bool playerInAir, playerJumping;
    bool playerRunning, playerCrouching;
    bool isCrouchHeld;

    void resetBackground(); // Make the background loop
    void inputHandler(); // Handle every input
    void updatePlayer(); // Update player state and position
    void updateBackground(); // Update background position
    void update(); // Handle logic per frame
    void render(); // Draw everything
    void run(); // Runs everything
};