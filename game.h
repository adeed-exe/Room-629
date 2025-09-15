#pragma once

#include "pch.h"
#include "player.h"
#include "menu.h"
#include "ViewSystem.h"
#include "hud.h"

class Game {
private:
    sf::Texture backgroundTexture;

    void initVariables();
    void initWindow();

public:
    Game();
    ~Game();

    sf::RenderWindow* window;
    ViewSystem* viewSystem;

    float deltaTime;
    sf::Clock dtClock;

    Player* player;
    Menu* menu;
    HUD* hud;
    sf::Sprite background;

    std::vector<sf::Text> mainMenuText;
    std::vector<sf::Text> controlsMenuText;


    //For level transition
    bool isTransitioning;
    float transitionAlpha;
    bool transitionFadeOut;

    bool isPauseAtBlack; // check if black
    float pauseCounter;    // counts time at black
    float transitionPause;

    sf::RectangleShape fadeRect;

    std:: vector<sf::FloatRect> doorBounds; // hitbox for door
    int doorNo;

    // Constants used across game
    float scale;
    float animationSpeed;
    int frameWidth, frameHeight;

    float playerMoveSpeed;
    float gravity;
    float ground;

    bool isInMenu, isInControlsMenu;
    bool isMouseHeld;

    sf::Vector2f playerVelocity;
    bool playerInAir, playerJumping;
    bool playerRunning;
    bool isEscapeHeld;

    void mainMenu(); // Display and handle the main menu
    void controlsMenu(); // Display and handle the controls menu
    void inputHandler(); // Handle every input
    void updatePlayer(); // Update player state and position
    void update(); // Handle logic per frame
    void render(); // Draw everything
    void run(); // Runs everything
    void debug(); // Debugging shenanigans
};
