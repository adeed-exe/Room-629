#pragma once

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
#include "Nightmare.h"
#include "Item.h"
#include "CutsceneManager.h"

class CutsceneManager;
class CutsceneSir;

class Game {
private:
    sf::Texture backgroundTexture;

    void initVariables();
    void initWindow();
    void initRooms();
    void buildCaches();

    void inputHandler();
    void nightmareAI();
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
    Nightmare* nightmare;
    CutsceneManager* cutscene;
    CutsceneSir* sir;


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
    std::vector<sf::Sprite> itemSprites;

    GameState gameState;
    const std::string savePath = "Assets/Save Files/saveFile.sav";

    // Constants and states used across game
    float scale;
    float animationSpeed;

    float playerMoveSpeed;
    float nightmareMoveSpeed;
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

    sf::Vector2f nightmareVelocity;
    bool nightmareAttacking, nightmareRunning;

    // For level transition
    bool isTransitioning;
    float transitionAlpha;
    bool transitionFadeOut;

    bool isPauseAtBlack; // Check if black
    float pauseCounter;    // Counts time at black
    float transitionPause;

    //For cutscenes
    sf::Vector2f sirPos;
    bool isCutsceneActive;
    bool allowPlayerInput;
    
    void playNewGameCutscene();
    void startCutscene();
    void endCutscene();
    void enablePlayerInput();

    Game();
    ~Game();

    void run();
    
    void startNewGame();
    void resetGame();
    void changeRoom(int targetRoomId, const sf::Vector2f& spawnOverride = { -1.f, -1.f });
};