#include "PCH.h"
#include "Game.h"

Game::Game()
    : background(backgroundTexture), titleScreenBackground(backgroundTexture)
{
    initVariables();
    initWindow();

    player = new Player(this);
    menu = new Menu(this);
    hud = new HUD(this);
    nightmare = new Nightmare(this);

    buildCaches();
    initRooms();

    auto& firstRoom = rooms.at(0);
    firstRoom.loadTexture();
    firstRoom.applyToSprite(background);
    itemSprites = hud->itemSprites;

    viewSystem = new ViewSystem(this);
    saveSystem = new SaveSystem(this);
    soundSystem = new SoundSystem(this);
    transition = new Transition(0.8f);

    if (!saveSystem->fileExists(savePath)) {
        saveSystem->save(savePath, gameState);
    }

    if (backgroundTexture.loadFromFile("Assets/Sprites/BG_titlescreen.png")) {
        std::cout << "Title Screen texture loaded!" << std::endl;
    }

    titleScreenBackground.setTexture(backgroundTexture, true);
    titleScreenBackground.setScale(sf::Vector2f({ 1920.f / backgroundTexture.getSize().x, 1080.f / backgroundTexture.getSize().y }));

    soundSystem->playBackgroundMusic();
}

Game::~Game() {
    delete player;
    delete menu;
    delete hud;
    delete viewSystem;
    delete saveSystem;
    delete soundSystem;
    delete transition;
    delete window;
    delete nightmare;
}

void Game::initVariables() {
    window = nullptr;

    scale = 4.f;
    animationSpeed = 0.08f;
    playerMoveSpeed = 150.f;
    nightmareMoveSpeed = 225.f;
    gravity = 880.f;
    ground = 180.f;

    autoSaveTimer = 0.f;
    autoSaveInterval = 60.f;

    isInTitleScreen = true;
    isInMenu = false;
    isInControlsMenu = false;
    isInConfirmationMenu = false;

    isMouseHeld = false;
    isEscapeHeld = false;
    isEnterHeld = false;

    playerVelocity = { 0.f, 0.f };
    playerInAir = false;
    playerJumping = false;
    playerRunning = false;

    nightmareVelocity = { 0.f, 0.f };
    nightmareAttacking = false;
    nightmareRunning = false;

    fadeRect.setSize({ 1920.f, 1080.f });
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));
}

void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "Room 629", sf::Style::None);
    window->setVerticalSyncEnabled(true);
}

void Game::buildCaches() {
    titleScreenText = menu->getTitleScreenText();
    mainMenuText = menu->getMainMenuText();
    controlsMenuText = menu->getControlsMenuText();
    confirmationMenuText = menu->getConfirmationMenuText();
}

void Game::initRooms() {
    Room r0(0, "Assets/Sprites/BG_room629.png", { 1253.f, ground });
    r0.addDoor(Door(0, sf::FloatRect({ 1228.f, 64.f }, { 82.f, 200.f }), 1, { 100.f, ground }));
    rooms.emplace(0, std::move(r0));

    Room r1(1, "Assets/Sprites/BG_hallway_6.png", { 100.f, ground });
    r1.addDoor(Door(0, sf::FloatRect({ 30.f, 64.f }, { 82.f, 200.f }), 0, { 1253.f, ground }));
    r1.addDoor(Door(1, sf::FloatRect({ 1115.f, 64.f }, { 82.f, 200.f }), 2, { 550.f, ground }));
    rooms.emplace(1, std::move(r1));

    Room r2(2, "Assets/Sprites/BG_office_room.png", { 100.f, ground });
    r2.addDoor(Door(0, sf::FloatRect({ 550.f, 64.f }, { 82.f, 200.f }), 1, { 1120.f, ground }));
    r2.addItem(Item(2, 0, sf::FloatRect({ 445.f, 64.f }, { 82.f, 300.f }), { 489.f, 97.f }));
    rooms.emplace(2, std::move(r2));


    std::cout << "======" << std::endl;
    for (auto& [roomId, room] : rooms) {
        std::cout << "Room " << roomId << " has " << room.getDoors().size() << " door: ";
        for (const Door& d : room.getDoors()) {
            std::cout << "Door ID: " << d.id
                << " -> Target Room: " << d.targetRoomId << " || ";
        }
        std::cout << std::endl;
        std::cout << "Room " << roomId << " has " << room.getItems().size() << " items: ";
        for (Item& i : room.getItems()) {
            std::cout << "Item ID: " << i.itemId
                << " -> Picked: " << gameState.roomInfo[gameState.currentRoomId] << " || ";
        }
        std::cout << std::endl;
    }
    std::cout << "======" << std::endl;
}

void Game::startNewGame() {
    gameState.items.clear();
    for (auto& x : gameState.roomInfo) {
        x = 0;
    }
    saveSystem->reset(savePath, gameState);
    changeRoom(0);
}

void Game::resetGame() {
    auto it = rooms.find(gameState.currentRoomId);
    if (it == rooms.end()) return;
    changeRoom(gameState.currentRoomId, it->second.getSpawn());
}

void Game::changeRoom(int targetRoomId, const sf::Vector2f& spawnOverride) {
    if (rooms.find(targetRoomId) == rooms.end()) return;

    transition->start([this, targetRoomId, spawnOverride]() {
        std::cout << "Changing to room: " << targetRoomId << "\n";
        gameState.currentRoomId = targetRoomId;

        Room& room = rooms.at(targetRoomId);
        if (!room.loadTexture())
            std::cout << "Failed to load room texture!\n";

        room.applyToSprite(background);
        background.setPosition(background.getLocalBounds().size / 2.f);

        // Use spawnOverride if valid, otherwise default room spawn
        sf::Vector2f spawn = (spawnOverride.x >= 0.f) ? spawnOverride : room.getSpawn();
        player->getPlayer().setPosition(spawn);
        player->getPlayer().setScale({ scale, scale });
        if (isInTitleScreen) {
            isInTitleScreen = false;
        }
        saveSystem->save(savePath, gameState);
        });
}


void Game::inputHandler() {
    playerRunning = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
    float moveSpeed = playerMoveSpeed;
    if (playerRunning && hud->stamina >= 1.f) moveSpeed *= 2.0f;

    playerVelocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && player->getPlayer().getPosition().x >= 68.f) {
        player->getPlayer().setScale({ -scale, scale });
        playerVelocity.x -= moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && player->getPlayer().getPosition().x <= (background.getLocalBounds().size.x - 68.f)) {
        player->getPlayer().setScale({ scale, scale });
        playerVelocity.x += moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && !playerInAir) {
        playerInAir = true;
        playerJumping = true;
        playerVelocity.y = -(playerMoveSpeed + 100.f);
    }

    auto it = rooms.find(gameState.currentRoomId);
    if (!transition->getIsTransitioning() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
        if (it != rooms.end()) {
            for (const Door& d : it->second.getDoors()) {
                if (d.bounds.contains(player->getPlayer().getPosition())) {
                    soundSystem->playDoorSound();
                    changeRoom(d.targetRoomId, d.spawnPos);
                    break;
                }
            }
            for (Item& i : it->second.getItems()) {
                if (i.bounds.contains(player->getPlayer().getPosition()) && !gameState.roomInfo[gameState.currentRoomId]) {
                    gameState.items.insert(i.itemId);
                    gameState.roomInfo[gameState.currentRoomId] = 1;
                    saveSystem->save(savePath, gameState);
                    break;
                }
            }
        }
    }
}

void Game::nightmareAI() {
    float distance = player->getPlayer().getPosition().x - nightmare->getNightmare().getPosition().x;
    nightmareRunning = (abs(distance) >= 200.f);
    float moveSpeed = nightmareMoveSpeed;
    if (nightmareRunning) moveSpeed *= 1.5f;

    nightmareVelocity.x = 0.f;
    nightmareAttacking = false;

    if (distance >= 50.f) {
        nightmare->getNightmare().setScale({ -2 * scale, 2 * scale });
        nightmareVelocity.x += moveSpeed;
    }
    else if (distance <= -50.f) {
        nightmare->getNightmare().setScale({ 2 * scale, 2 * scale });
        nightmareVelocity.x -= moveSpeed;
    }
    else {
        nightmareAttacking = true;
    }
}

void Game::update() {
    deltaTime = dtClock.restart().asSeconds();

    gameState.curStamina = hud->stamina;
    gameState.curFatigue = hud->fatigue;
    gameState.playerPos = player->getPlayer().getPosition();

    autoSaveTimer += deltaTime;
    if (autoSaveTimer >= autoSaveInterval) {
        autoSave();
    }

    if (player->getPlayer().getPosition().y > ground - 1.f) {
        playerInAir = false;
        playerVelocity.y = 0.f;
        player->getPlayer().setPosition({ player->getPlayer().getPosition().x, ground });
    }

    transition->update(deltaTime);

    inputHandler();

    nightmareAI();

    if (playerInAir) playerVelocity.y += gravity * deltaTime;

    player->getPlayer().move(playerVelocity * deltaTime);
    nightmare->getNightmare().move(nightmareVelocity * deltaTime);

    if (playerJumping) player->animateJump();
    else if (playerVelocity.x != 0.f && playerRunning && hud->stamina >= 1.f) player->animateRun();
    else if (playerVelocity.x != 0.f) player->animateWalk();
    else player->animateIdle();

    if (nightmareAttacking) nightmare->animateAttack();
    else if (nightmareVelocity.x != 0.f && nightmareRunning) nightmare->animateRun();
    else if (nightmareVelocity.x != 0.f) nightmare->animateWalk();
    else nightmare->animateIdle();

    viewSystem->update(player->getPlayer().getPosition());
    hud->update(deltaTime, playerRunning && playerVelocity.x != 0.f);
}

void Game::render() {
    window->clear();
    window->draw(background);

    if (!isInMenu && !isInControlsMenu && !isInTitleScreen && !isInConfirmationMenu) {
        window->setView(viewSystem->getView());
        window->draw(player->getPlayer());
        // window->draw(nightmare->getNightmare());
        hud->render(*window);
        auto it = rooms.find(gameState.currentRoomId);
        if (it != rooms.end()) {
            for (const Door& d : it->second.getDoors()) {
                if (d.bounds.contains(player->getPlayer().getPosition())) {
                    sf::Vector2f buttonPos(d.bounds.position.x + d.bounds.size.x / 2.f - 11.75f, 90.f);
                    player->getInteractButton().setPosition(buttonPos);
                    window->draw(player->getInteractButton());
                    break;
                }
            }
            for (Item& i : it->second.getItems()) {
                sf::Sprite temp = itemSprites[i.itemId];
                temp.setPosition(i.drawPos);
                if (i.roomId == gameState.currentRoomId && !gameState.roomInfo[gameState.currentRoomId]) {
                    window->draw(temp);
                }
                if (i.bounds.contains(player->getPlayer().getPosition()) && !gameState.roomInfo[gameState.currentRoomId]) {
                    sf::Vector2f buttonPos(i.drawPos.x, i.drawPos.y - 20);
                    player->getInteractButton().setPosition(buttonPos);
                    window->draw(player->getInteractButton());
                    break;
                }
            }
        }
    }
    else {
        window->setView(window->getDefaultView());
        if (isInTitleScreen) {
            window->draw(titleScreenBackground);
            for (int i = 0; i < titleScreenText.size(); i++) {
                window->draw(titleScreenText[i]);
            }
        }
        if (isInMenu) {
            for (int i = 0; i < mainMenuText.size(); i++) {
                window->draw(mainMenuText[i]);
            }
        }
        else if (isInControlsMenu) {
            for (int i = 0; i < controlsMenuText.size(); i++) {
                window->draw(controlsMenuText[i]);
            }
        }
        else if (isInConfirmationMenu) {
            for (int i = 0; i < confirmationMenuText.size(); i++) {
                window->draw(confirmationMenuText[i]);
            }
        }
    }

    transition->render(*window);
    window->display();
}

void Game::debug() {
    // sf::Vector2f mousePos(sf::Mouse::getPosition(*window));
    // std::cout << mousePos.x << " " << mousePos.y << std::endl;
    // std::cout << player->getPlayer().getPosition().x << std::endl;
}

void Game::titleScreen() {
    sf::Vector2f mousePos(sf::Mouse::getPosition(*window));
    bool isEnterPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    if (isEnterPressed && !isEnterHeld) {
        soundSystem->playStartSound();
        saveSystem->load(savePath, gameState);
        changeRoom(gameState.currentRoomId, gameState.playerPos);
    }
    isEnterHeld = isEnterPressed;

    if (titleScreenText[1].getGlobalBounds().contains(mousePos)) {
        titleScreenText[1].setFillColor(sf::Color(150, 150, 150)); // Darken button while hovering
        bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (isMousePressed && !isMouseHeld) {
            soundSystem->playStartSound();
            saveSystem->load(savePath, gameState);
            changeRoom(gameState.currentRoomId, gameState.playerPos);
        }
        isMouseHeld = isMousePressed;
    }
    else {
        titleScreenText[1].setFillColor(sf::Color(255, 255, 255));
    }
}

void Game::mainMenu() {
    sf::Vector2f mousePos(sf::Mouse::getPosition(*window));
    for (int i = 0; i < mainMenuText.size(); i++) {
        if (mainMenuText[i].getGlobalBounds().contains(mousePos)) {
            mainMenuText[i].setFillColor(sf::Color(150, 150, 150)); // Darken button while hovering
            bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
            if (isMousePressed && !isMouseHeld) {
                soundSystem->playButtonSound();
                if (i == 0) { // Continue
                    resumeGame();
                }
                else if (i == 1) { // New game
                    lastMenuAction = 0;
                    isInConfirmationMenu = true;
                    isInMenu = false;
                }
                else if (i == 2) { // Controls
                    isInControlsMenu = true;
                    isInMenu = false;
                }
                else if (i == 3) { // Exit
                    lastMenuAction = 1;
                    isInConfirmationMenu = true;
                    isInMenu = false;
                }
            }
            isMouseHeld = isMousePressed;
        }
        else {
            mainMenuText[i].setFillColor(sf::Color(255, 255, 255));
        }
    }
}

void Game::controlsMenu() {
    sf::Vector2f mousePos(sf::Mouse::getPosition(*window));
    if (controlsMenuText[4].getGlobalBounds().contains(mousePos)) {
        controlsMenuText[4].setFillColor(sf::Color(150, 150, 150)); // Darken button while hovering
        bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (isMousePressed && !isMouseHeld) {
            soundSystem->playButtonSound();
            isInMenu = true;
            isInControlsMenu = false;
        }
        isMouseHeld = isMousePressed;
    }
    else {
        controlsMenuText[4].setFillColor(sf::Color(255, 255, 255));
    }
}

void Game::confirmationMenu() {
    sf::Vector2f mousePos(sf::Mouse::getPosition(*window));
    for (int i = 1; i < confirmationMenuText.size(); i++) {
        if (confirmationMenuText[i].getGlobalBounds().contains(mousePos)) {
            confirmationMenuText[i].setFillColor(sf::Color(150, 150, 150)); // Darken button while hovering
            bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
            if (isMousePressed && !isMouseHeld) {
                soundSystem->playButtonSound();
                if (i == 1) { // No
                    isInConfirmationMenu = false;
                    isInMenu = true;
                }
                else if (i == 2) { // Yes
                    isInConfirmationMenu = false;
                    if (lastMenuAction == 0) {
                        startNewGame();
                        resumeGame();
                    }
                    else {
                        exitGame();
                    }
                }
            }
            isMouseHeld = isMousePressed;
        }
        else {
            confirmationMenuText[i].setFillColor(sf::Color(255, 255, 255));
        }
    }
}

void Game::pauseGame() {
    soundSystem->playButtonSound();
    if (!isInMenu && !isInControlsMenu && !isInConfirmationMenu) {
        isInMenu = true;
        background.setColor(sf::Color(255, 255, 255, 125)); // Darken background while in menu
    }
    else if (!isInMenu && isInControlsMenu) {
        isInControlsMenu = false;
        isInMenu = true;
    } else if (!isInMenu && isInConfirmationMenu) {
        isInConfirmationMenu = false;
        isInMenu = true;
    }
    else if (isInMenu) {
        isInMenu = false;
        isInControlsMenu = false;
        background.setColor(sf::Color(255, 255, 255, 255)); // Revert darkening the background
    }
}

void Game::resumeGame() {
    isInMenu = false;
    background.setColor(sf::Color(255, 255, 255, 255));
}

void Game::exitGame() {
    saveSystem->save(savePath, gameState);
    window->close();
}

void Game::autoSave() {
    saveSystem->save(savePath, gameState);
    std::cout << "Game auto-saved!\n";
    autoSaveTimer = 0.f; // Reset timer
}

void Game::run() {
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }

            // Toggle main menu
            bool isEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
            if (isEscapePressed && !isEscapeHeld && !isInTitleScreen) {
                pauseGame();
            }
            isEscapeHeld = isEscapePressed;
        }
        if (isInTitleScreen) {
            titleScreen();
        }
        if (isInMenu) {
            mainMenu();
        }
        else if (isInControlsMenu) {
            controlsMenu();
        }
        else if (isInConfirmationMenu) {
            confirmationMenu();
        }
        else {
            update();
        }
        render();
        debug();
    }
}