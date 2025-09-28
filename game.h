#pragma once

#include "PCH.h"
#include "Player.h"
#include "Menu.h"
#include "ViewSystem.h"
#include "HUD.h"
#include "Transition.h"
#include "Door.h"
#include "Room.h"

class Game {
private:
    sf::Texture backgroundTexture;

    void initVariables();
    void initWindow();
    void initRooms();
    void buildCaches();

    void inputHandler();
    void update();
    void render();
    void debug();
    void titleScreen();
    void mainMenu();
    void controlsMenu();

    void pauseGame();
    void resumeGame();
    void exitGame();

public:
    // Getters used by other subsystems
    sf::RenderWindow* getWindow() { return window; }

    sf::RenderWindow* window;

    float deltaTime;
    sf::Clock dtClock;

    Player* player;
    Menu* menu;
    HUD* hud;
    Door* door;
    Room* room;
    ViewSystem* viewSystem;
    Transition* transition;
    sf::Sprite background;
    sf::Sprite titleScreenBackground;

    std::map<int, Room> rooms;
    int currentRoomId = 0;

    std::vector<sf::Text> titleScreenText;
    std::vector<sf::Text> mainMenuText;
    std::vector<sf::Text> controlsMenuText;

    // For level transition
    bool isTransitioning;
    float transitionAlpha;
    bool transitionFadeOut;

    bool isPauseAtBlack; // Check if black
    float pauseCounter;    // Counts time at black
    float transitionPause;

    sf::RectangleShape fadeRect;

    std::vector<Door*> doors;
    int doorNo;

    // Constants and states used across game
    float scale;
    float animationSpeed;
    int frameWidth, frameHeight;

    float playerMoveSpeed;
    float gravity;
    float ground;

    bool isInTitleScreen;
    bool isInMenu, isInControlsMenu;
    bool isMouseHeld, isEscapeHeld;

    sf::Vector2f playerVelocity;
    bool playerInAir, playerJumping;
    bool playerRunning;

    Game();
    ~Game();

    void run();
    
    void startNewGame();
    void resetGame();
    void changeRoom(int targetRoomId, const sf::Vector2f& spawnOverride = { -1.f, -1.f });
};