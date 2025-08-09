#pragma once

#include "pch.h"
#include "player.h"
#include "menu.h"
#include "ViewSystem.h"

class Game {
private:
    sf::Texture backgroundTexture;

    void initVariables(); // Initialize member variables
    void initWindow(); // Create window with settings
    void initViewSystem(); // initialize the viewer 

public:
    Game(); // Constructor
    ~Game(); // Destructor

    sf::RenderWindow* window; // Pointer to game window

    ViewSystem* viewSystem; // view system for the sidescroller

    float deltaTime; // Time between frames
    sf::Clock dtClock; // Clock to measure deltaTime

    // Player/Background/Menu instances
    Player* player;
    sf::Sprite background;
    Menu* menu;
    std::vector<sf::Text> mainMenuText;
    std::vector<sf::Text> controlsMenuText;

    // Constants used across game
    float scale;
    float animationSpeed;
    int frameWidth, frameHeight;

    float playerMoveSpeed;
    float gravity;
    float ground;

    // Game states
    bool isInMenu, isInControlsMenu;
    bool isMouseHeld;

    // Player states
    sf::Vector2f playerVelocity;
    bool playerInAir, playerJumping;
    bool playerRunning, playerCrouching;
    bool isCrouchHeld;

    void mainMenu(); // Display and handle the main menu
    void controlsMenu(); // Display and handle the controls menu
    void inputHandler(); // Handle every input
    void updatePlayer(); // Update player state and position
    void update(); // Handle logic per frame
    void render(); // Draw everything
    void run(); // Runs everything
};