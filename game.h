﻿#pragma once

#include "PCH.h"
#include "Player.h"
#include "Menu.h"
#include "HUD.h"
#include "ViewSystem.h"
#include "SaveSystem.h"
#include "SoundSystem.h"
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
    void confirmationMenu();

    void pauseGame();
    void resumeGame();
    void exitGame();
    void autoSave();

public:
    // Getters used by other subsystems
    sf::RenderWindow* getWindow() { return window; }

    sf::RenderWindow* window;

    // Other class instances
    Player* player;
    Menu* menu;
    HUD* hud;
    Transition* transition;
    ViewSystem* viewSystem;
    SaveSystem* saveSystem;
    SoundSystem* soundSystem;

    sf::Sprite background;
    sf::Sprite titleScreenBackground;
    sf::RectangleShape fadeRect;

    float deltaTime;
    sf::Clock dtClock;

    std::map<int, Room> rooms;

    std::vector<Door*> doors;

    std::vector<sf::Text> titleScreenText;
    std::vector<sf::Text> mainMenuText;
    std::vector<sf::Text> controlsMenuText;
    std::vector<sf::Text> confirmationMenuText;

    GameState gameState;
    const std::string savePath = "Assets/Save Files/saveFile.sav";

    // Constants and states used across game
    float scale;
    float animationSpeed;
    int frameWidth, frameHeight;

    float playerMoveSpeed;
    float gravity;
    float ground;

    float autoSaveTimer;
    float autoSaveInterval;

    bool isInTitleScreen, isInMenu;
    bool isInControlsMenu, isInConfirmationMenu;
    int lastMenuAction; // 0 = New game, 1 = Exit;

    bool isMouseHeld, isEscapeHeld;
    bool isEnterHeld;

    sf::Vector2f playerVelocity;
    bool playerInAir, playerJumping;
    bool playerRunning;

    // For level transition
    bool isTransitioning;
    float transitionAlpha;
    bool transitionFadeOut;

    bool isPauseAtBlack; // Check if black
    float pauseCounter;    // Counts time at black
    float transitionPause;

    Game();
    ~Game();

    void run();
    
    void startNewGame();
    void resetGame();
    void changeRoom(int targetRoomId, const sf::Vector2f& spawnOverride = { -1.f, -1.f });
};