#include "PCH.h"
#include "Game.h"

Game::Game()
    : background(backgroundTexture), titleScreenBackground(titleScreenBackgroundTexture), menuBackground(menuBackgroundTexture),
    menuLeftHand(leftHandTexture), menuRightHand(rightHandTexture), cursor(cursorTexture), vignette(vignetteTexture)
{
    initVariables();
    initWindow();

    player = new Player(this);
    menu = new Menu(this);
    hud = new HUD(this);
    nightmare = new Nightmare(this);
    sir = new CutsceneSir(this);

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
    cutscene = new CutsceneManager();

    if (!saveSystem->fileExists(savePath)) {
        saveSystem->save(savePath, gameState);
    }

    if (backgroundTexture.loadFromFile("Assets/Sprites/BG_titlescreen.png")) {
        std::cout << "Title Screen texture loaded!" << std::endl;
    }

    sf::Vector2f scaleRatio{ 1920.f / backgroundTexture.getSize().x, 1080.f / backgroundTexture.getSize().y };

    titleScreenBackground.setTexture(backgroundTexture, true);
    titleScreenBackground.setScale(scaleRatio);

    if (menuBackgroundTexture.loadFromFile("Assets/Sprites/BG_menu.png")) {
        std::cout << "Menu texture loaded!" << std::endl;
    }

    menuBackground.setTexture(menuBackgroundTexture, true);
    menuBackground.setScale(scaleRatio);
    
    if (leftHandTexture.loadFromFile("Assets/Sprites/BG_menu_left_hand.png")) {
        std::cout << "Menu left hand texture loaded!" << std::endl;
    }

    menuLeftHand.setTexture(leftHandTexture, true);
    menuLeftHand.setScale(scaleRatio);
    
    if (rightHandTexture.loadFromFile("Assets/Sprites/BG_menu_right_hand.png")) {
        std::cout << "Menu right hand texture loaded!" << std::endl;
    }

    menuRightHand.setTexture(rightHandTexture, true);
    menuRightHand.setScale(scaleRatio);
    
    if (rightHandClickTexture.loadFromFile("Assets/Sprites/BG_menu_right_hand_click.png")) {
        std::cout << "Menu right hand texture loaded!" << std::endl;
    }

    if (cursorTexture.loadFromFile("Assets/Sprites/cursor_titleScreen.png")) {
        std::cout << "Cursor texture loaded!" << std::endl;
    }

    if (vignetteTexture.loadFromFile("Assets/Sprites/vignette.png")) {
        std::cout << "Vignette texture loaded!" << std::endl;
    }

    cursor.setTexture(cursorTexture, true);
    cursor.setOrigin(cursor.getGlobalBounds().size / 2.f);

    vignette.setTexture(vignetteTexture, true);
    vignette.setColor(sf::Color(255, 255, 255, 0));

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
    delete cutscene;
    delete sir;
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
    cursorTriggered = false;

    playerVelocity = { 0.f, 0.f };
    playerInAir = false;
    playerJumping = false;
    playerRunning = false;

    nightmareVelocity = { 0.f, 0.f };
    nightmareAttacking = false;
    nightmareRunning = false;
    isNightmareHaunting = false;

    isCutsceneActive = false;
    allowPlayerInput = true;
    sirPos = sf::Vector2f({ 1100.f, ground });

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
    Room r0(0, "Assets/Sprites/BG_room629.png", { 930.f, ground });
    r0.addDoor(Door(0, sf::FloatRect({ 1228.f, 64.f }, { 82.f, 200.f }), 1, { 100.f, ground }));
    rooms.emplace(0, std::move(r0));

    Room r1(1, "Assets/Sprites/BG_hallway_6.png", { 100.f, ground });
    r1.addDoor(Door(0, sf::FloatRect({ 30.f, 64.f }, { 82.f, 200.f }), 0, { 1253.f, ground }));
    r1.addDoor(Door(1, sf::FloatRect({ 1115.f, 64.f }, { 82.f, 200.f }), 2, { 550.f, ground }));
    r1.addDoor(Door(2, sf::FloatRect({ 1010.f, 64.f }, { 82.f, 200.f }), 3, { 1010.f, ground }));
    rooms.emplace(1, std::move(r1));

    Room r2(2, "Assets/Sprites/BG_office_room.png", { 100.f, ground });
    r2.addDoor(Door(0, sf::FloatRect({ 550.f, 64.f }, { 82.f, 200.f }), 1, { 1120.f, ground }));
    r2.addItem(Item(2, 0, sf::FloatRect({ 445.f, 64.f }, { 82.f, 300.f }), { 489.f, 97.f }));
    rooms.emplace(2, std::move(r2));

    Room r3(3, "Assets/Sprites/BG_hallway_3.png", { 1000.f, ground });
    r3.addDoor(Door(0, sf::FloatRect({ 30.f, 64.f }, { 82.f, 200.f }), 4, { 1253.f, ground }));
    r3.addDoor(Door(1, sf::FloatRect({ 762.f, 64.f }, { 82.f, 200.f }), 1, { 762.f, ground }));
    //r3.addItem(Item(3, 0, sf::FloatRect({ 445.f, 64.f }, { 82.f, 300.f }), { 489.f, 97.f }));
    rooms.emplace(3, std::move(r3));

    Room r4(4, "Assets/Sprites/BG_room629.png", { 930.f, ground });
    r4.addDoor(Door(0, sf::FloatRect({ 1228.f, 64.f }, { 82.f, 200.f }), 3, { 100.f, ground }));
    rooms.emplace(4, std::move(r4));



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

    playNewGameCutscene();
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
        },400.f, 500.f, 0.8f);
}


void Game::inputHandler() {

    //player movement
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
    
    //button presses
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

void Game::startCutscene() {
    isCutsceneActive = true;
    allowPlayerInput = false;
}

void Game::endCutscene() {
    isCutsceneActive = false;
}

void Game::enablePlayerInput() {
    allowPlayerInput = true;
}



void Game::playNewGameCutscene() {
    sirPos.x = 1250.f;
    sirPos.y = ground-2.f;

    startCutscene(); // disable input

    /* cutscene desc
    
    Move right 
    Wait 3 second
    Show dialogue
    Move left
    Move right 
    End cutscene*/
        
    //cutscene->addAction(new DialogueAction("I will show a dialogue text when this happens"));
    cutscene->addAction(new WaitAction(0.8f));

    cutscene->addAction(new TurnAction(1.f));
    cutscene->addAction(new TurnAction(1.5f));

    cutscene->addAction(new WaitAction(0.8f));


    cutscene->addAction(new DialogueAction("Where's everyone? Did I doze off again", 3.f));
    cutscene->addAction(new DialogueAction("Teacher: I was waiting for you to wake up..", 3.f));


    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(150.f, 0.f)));
    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(150.f, 0.f)));
    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(150.f, 0.f)));

    cutscene->addAction(new WaitAction(0.2f));
    

    cutscene->addAction(new DialogueAction(". . .", 1.f));
    cutscene->addAction(new DialogueAction("Teacher : Everyone has already left.", 3.f));
    cutscene->addAction(new DialogueAction("Teacher : I had some work left here, and I need some help..", 3.f));
    cutscene->addAction(new DialogueAction("Teacher : Since you are here already..", 3.f));
    cutscene->addAction(new DialogueAction("Sorry Sir, I was feeling extremely tired. But I feel okay right now.", 3.f));
    cutscene->addAction(new DialogueAction("Teacher : It would be great if you could get me my papers from room Gallery-2.", 3.5f));
    cutscene->addAction(new DialogueAction("Teacher : It's on the Table.", 3.f));

    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(-100.f, 0.f)));
    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(-100.f, 0.f)));
    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(-100.f, 0.f)));
    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(-100.f, 0.f)));

    cutscene->addAction(new EndCutsceneAction());

    cutscene->start();


    gameState.progress = 1;

    saveSystem->save(savePath, gameState);
}


void Game::cutsceneOfficeRoom() {
    sirPos.x = 100.806f;
    sirPos.y = ground-2.f;

    sir->getSir().setScale({ sir->getSir().getScale().x * (-1), sir->getSir().getScale().y });

    startCutscene(); // disable input

    /* cutscene desc

    Look about
    sir talks
    Wait 
    goes toward sir
    show dialogues   
    goes toward door
    End cutscene*/

    //cutscene->addAction(new DialogueAction("I will show a dialogue text when this happens"));
    cutscene->addAction(new WaitAction(0.4f));
    
    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(-100.f, 0.f)));
    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(-100.f, 0.f)));
    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(-100.f, 0.f)));
    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(-100.f, 0.f)));
    cutscene->addAction(new MoveAction(0.5f, sf::Vector2f(-100.f, 0.f)));

    cutscene->addAction(new DialogueAction("Teacher : You got the papers, right?", 3.f));
    gameState.items.erase(3);
    saveSystem->save(savePath, gameState);
    cutscene->addAction(new DialogueAction("*Player gives the paper to Teacher*", 3.f));
    cutscene->addAction(new DialogueAction("Teacher : Alright, you can go. Thanks for the help. See you tomorrow.", 3.f));
    cutscene->addAction(new DialogueAction("Player : See you tomorrow, Sir.", 3.f));
    //cutscene->addAction(new DialogueAction("I should go to home.", 3.f));
   /* cutscene->addAction(new DialogueAction("", 3.f));
    cutscene->addAction(new DialogueAction("", 3.f));
    cutscene->addAction(new DialogueAction("", 3.f));
    cutscene->addAction(new DialogueAction("", 3.f));
    cutscene->addAction(new DialogueAction("", 3.f));
    cutscene->addAction(new DialogueAction("", 3.f));*/


    cutscene->addAction(new EndCutsceneAction());

    cutscene->start();

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

    cutscene->update(deltaTime, this);

    if (allowPlayerInput) {
        inputHandler();
    }
    if (cutscene->isRunning()) {

        sir->animateIdle();   // update your frame animation
    }

    if (isNightmareHaunting) {
        vignetteAlpha += 30;
        if (vignetteAlpha > 255) {
            vignetteAlpha = 255;
        }
        vignette.setColor(sf::Color(255, 255, 255, vignetteAlpha));
        nightmareAI();
    }
    else {
        nightmare->getNightmare().setPosition({ 1920, ground + 22 });
    }

    if (hud->fatigue >= 99) {
        isNightmareHaunting = true;
    }

    if (isNightmareHaunting && hud->stamina < 50) {
        isNightmareHaunting = false;
        vignetteAlpha = 0;
        vignette.setColor(sf::Color(255, 255, 255, vignetteAlpha));
    }

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

    if (gameState.progress == 1 && gameState.currentRoomId == 2) {
        auto it = gameState.items.find(3);
        if (it != gameState.items.end())
        {
            cutsceneOfficeRoom();            
        }

        if (!cutscene->isRunning()) {

            changeRoom(1, { 1120.f, ground });


            gameState.progress = 2;

            saveSystem->save(savePath, gameState);

            cutscene->start();
            cutscene->addAction(new WaitAction(4.f));

            cutscene->addAction(new DialogueAction("I should go home..", 3.f));
        }
    }
}

void Game::render() {
    window->clear();
    window->draw(background);
    if (cutscene->isRunning()) {
        window->draw(sir->getSir());
    }

    if (!isInMenu && !isInControlsMenu && !isInTitleScreen && !isInConfirmationMenu) {
        window->setView(viewSystem->getView());
        window->draw(player->getPlayer());

        if (isNightmareHaunting) {
            window->draw(nightmare->getNightmare());
        }

        if (hud->subtitleVisible) {
            window->draw(hud->subtitleText);
        }
         
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
            window->draw(cursor);
        }
        else {
            window->draw(menuBackground);
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
            window->draw(menuLeftHand);
            window->draw(menuRightHand);
        }
    }

    transition->render(*window);
    window->draw(vignette);
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
        window->setMouseCursorVisible(true);
    }
    isEnterHeld = isEnterPressed;

    if (titleScreenText[1].getGlobalBounds().contains(mousePos)) {
        titleScreenText[1].setFillColor(sf::Color(150, 150, 150)); // Darken button while hovering
        bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (isMousePressed && !isMouseHeld) {
            soundSystem->playStartSound();
            saveSystem->load(savePath, gameState);
            changeRoom(gameState.currentRoomId, gameState.playerPos);
            window->setMouseCursorVisible(true);
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

            sf::Vector2f mousePos(sf::Mouse::getPosition(*window));
            menuRightHand.setPosition({ mousePos.x - 20.f, mousePos.y - 20.f });
            cursor.setPosition({ mousePos.x - 20.f, mousePos.y - 20.f });
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                menuRightHand.setTexture(rightHandClickTexture, true);
                menuRightHand.move({ -18, 0 });
            }
            else {
                menuRightHand.setTexture(rightHandTexture, true);
            }

            if (isInMenu || isInConfirmationMenu || isInControlsMenu || isInTitleScreen) {
                window->setMouseCursorVisible(false);
            }
            else {
                window->setMouseCursorVisible(true);
            }
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