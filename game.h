#pragma once

#include "pch.h"
#include "player.h"
#include "menu.h"

class Game {
private:
    sf::Texture backgroundTexture;

    void initVariables(); // Initialize member variables
    void initWindow(); // Create window with settings

public:
    Game(); // Constructor
    ~Game(); // Destructor

    sf::RenderWindow* window; // Pointer to game window

    float deltaTime; // Time between frames
    sf::Clock dtClock; // Clock to measure deltaTime

    // Player/Background/Menu instances
    Player* player;
    sf::Sprite background;
    Menu* menu;
    std::vector<sf::Sprite> buttons;

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

    void inputHandler(); // Handle every input
    void updatePlayer(); // Update player state and position
    void update(); // Handle logic per frame
    void render(); // Draw everything
    void run(); // Runs everything
};