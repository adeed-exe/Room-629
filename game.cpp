#include "pch.h"
#include "game.h"

// Private
void Game::initVariables() {
    window = nullptr;

    //variables for 
    
    // animation of characters
    frameWidth = 43;
    frameHeight = 43;
    scale = 4.f;
    animationSpeed = 0.08f;
    playerMoveSpeed = 150.f;
    gravity = 880.f;
    ground = 180.f;
    
    //menu naviagation
    isInMenu = true;
    isInControlsMenu = false;
    isMouseHeld = false;

    //player speed and jump mechanic
    playerVelocity = { 0.f, 0.f };
    playerInAir = false;
    playerJumping = false;
    playerRunning = false;
    isEscapeHeld = false;

    //transition effect
    isTransitioning = false;
    transitionAlpha = 0.f;
    transitionFadeOut = true;
    isPauseAtBlack = false;
    pauseCounter = 0.f;
    transitionPause = 1.f;

    //Floor and Door counters
    
    doorNo = 0;

    doorBounds = { { { 1212, 64 } , { 82, 200 }} ,  { { 1212, 64 } , { 82, 200 } } };

    fadeRect.setSize(sf::Vector2f(1920.f, 1080.f));
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));

    // Fade overlay
    fadeRect.setSize(sf::Vector2f(1920.f, 1080.f));
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));

    //Load backgrounds and set parameters
    if (backgroundTexture.loadFromFile("Assets/Sprites/Room629_BG_01.png")) {
        std::cout << "Background texture loaded!" << std::endl;
    }
    background.setTexture(backgroundTexture, true);
    background.setColor(sf::Color(255, 255, 255, 125));
    background.setOrigin(background.getLocalBounds().size / 2.f);

    //now set to the top of the screen for easier calculation
    background.setPosition({ 960.f, 150.f});
}

void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "Room 629", sf::Style::None);
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(true);
}

// Public
Game::Game() : background(backgroundTexture) {
    initVariables();
    initWindow();
    player = new Player(this);
    menu = new Menu(this);
    hud = new HUD(this);
    viewSystem = new ViewSystem(this);
    Transition = new transition(0.8f);

    mainMenuText = menu->getMainMenuText();
    controlsMenuText = menu->getControlsMenuText();
}

Game::~Game() {
    delete player;
    delete menu;
    delete hud;    
    delete window;
    delete viewSystem;
    delete Transition;
}

void Game::mainMenu() {
    sf::Vector2f mousePos(sf::Mouse::getPosition(*window));
    for (int i = 0; i < mainMenuText.size(); i++) {
        if (mainMenuText[i].getGlobalBounds().contains(mousePos)) {
            mainMenuText[i].setFillColor(sf::Color(150, 150, 150)); // Darken button while hovering
            int isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
            if (isMousePressed && !isMouseHeld) {
                if (i == 0) {
                    isInMenu = false;
                    background.setColor(sf::Color(255, 255, 255, 255));
                }
                else if (i == 2) {
                    isInControlsMenu = true;
                    isInMenu = false;
                }
                else if (i == 3) {
                    window->close();
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
        int isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (isMousePressed && !isMouseHeld) {
            isInMenu = true;
            isInControlsMenu = false;
        }
        isMouseHeld = isMousePressed;
    }
    else {
        controlsMenuText[4].setFillColor(sf::Color(255, 255, 255));
    }
}

void Game::inputHandler() {
    playerRunning = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);

    float moveSpeed = playerMoveSpeed;

    if (playerRunning && hud->stamina >= 1) {
        moveSpeed *= 2.0f; // Increase speed while running
    }

    // Move left and right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && player->getPlayer().getPosition().x >= 68) {
        player->getPlayer().setScale({ -scale, scale });
        playerVelocity.x -= moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && player->getPlayer().getPosition().x <= (background.getLocalBounds().size.x - 68)) {
        player->getPlayer().setScale({ scale, scale });
        playerVelocity.x += moveSpeed;
    }

    // Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && !playerInAir) {
        playerInAir = true;
        playerJumping = true;
        playerVelocity.y = -(playerMoveSpeed + 100.f);
    }

    // Check door interaction
    if (!Transition->getIsTransitioning() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
        if (doorBounds[doorNo].contains(player->getPlayer().getPosition())) {
            Transition->start();
            doorNo = 1;
        }
    }
}

void Game::updatePlayer() {
    if (playerJumping) {
        player->animateJump();
    }
    else if (playerVelocity.x && playerRunning && hud->stamina >= 1) {
        player->animateRun();
    }
    else if (playerVelocity.x) {
        player->animateWalk();
    }
    else {
        player->animateIdle();
    }
}

void Game::update() {
    deltaTime = dtClock.restart().asSeconds();

    playerVelocity.x = 0;
    playerRunning = false;

    // Clamp player to ground
    if (player->getPlayer().getPosition().y > ground - 1) {
        playerInAir = false;
        playerVelocity.y = 0;
        player->getPlayer().setPosition({ player->getPlayer().getPosition().x, ground });
    }

    //--------transition (TEMPORARY - WILL MAKE A NEW CLASS FOR IT)-------
    /*
        summary 
        if press F start transition
        turn up the alpha of the black filter until max
        when max alpha, change load new background
        turn down the alpha till min
    


    if (isTransitioning) {
        if (transitionFadeOut) {
            // Fade out
            transitionAlpha += 200.f * deltaTime;
            if (transitionAlpha >= 255.f) {
                transitionAlpha = 255.f;

                // Load new background immediately when screen is black
                if (!isPauseAtBlack && transitionAlpha == 255) {
                    if (backgroundTexture.loadFromFile("Assets/Sprites/Room629_BG_Hallway.png")) {
                        background.setTexture(backgroundTexture, true);
                    }
                    isPauseAtBlack = true; // start pause timer
                    pauseCounter = 0.f;
                    player->getPlayer().setScale({ scale, scale });
                    player->getPlayer().setPosition(sf::Vector2f({ 80, player->getPlayer().getPosition().y }));
                }

                // Count pause duration
                pauseCounter += deltaTime;
                if (pauseCounter >= transitionPause) {
                    transitionFadeOut = false;   // start fade-in
                    isPauseAtBlack = false;
                    pauseCounter = 0.f;
                }
            }
        }
        else {
            transitionAlpha -= 200 * deltaTime;
            if (transitionAlpha <= 0) {
                transitionAlpha = 0;
                isTransitioning = false; // Transition finished
            }
        }

        fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<uint8_t>(transitionAlpha)));
    }
    */
    Transition->update(deltaTime, [this]() {
        // this runs once when fully black
        if (backgroundTexture.loadFromFile("Assets/Sprites/Room629_BG_Hallway.png")) {
            background.setTexture(backgroundTexture, true);
        }
        player->getPlayer().setScale({ scale, scale });
        player->getPlayer().setPosition({ 80, player->getPlayer().getPosition().y });
        });

    //------------------------------------------------------------------


    inputHandler();

    if (playerInAir) {
        playerVelocity.y += gravity * deltaTime;
    }

    player->getPlayer().move(playerVelocity * deltaTime);

    updatePlayer();

    viewSystem->update(player->getPlayer().getPosition());

    hud->update(deltaTime, playerRunning && playerVelocity.x);
}

void Game::render() {
    window->clear();

    window->draw(background);

    if (!isInMenu && !isInControlsMenu) {
        window->setView(viewSystem->getView());
        window->draw(player->getPlayer());
        hud->render(*window);
    }
    else {
        window->setView(window->getDefaultView());
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
    }

    if (doorBounds[doorNo].contains(player->getPlayer().getPosition())) {
        sf::FloatRect door = doorBounds[doorNo];
        sf::Vector2f doorPos = door.position;
        sf::Vector2f doorSize = door.size;
        sf::Vector2f buttonPos;
        buttonPos.x = doorPos.x + doorSize.x / 2.f - 11.75f;
        buttonPos.y = 90;
        player->getInteractButton().setPosition(buttonPos);
        window->draw(player->getInteractButton());
    }

    Transition->render(*window);

    window->display();
}

void Game::run() {
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }

            // Toggle main menu
            bool isEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
            if (isEscapePressed && !isEscapeHeld) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && !isInMenu && !isInControlsMenu) {
                    isInMenu = true;
                    background.setColor(sf::Color(255, 255, 255, 125)); // Darken background while in menu
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && !isInMenu && isInControlsMenu) {
                    isInControlsMenu = false;
                    isInMenu = true;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && isInMenu) {
                    isInMenu = false;
                    isInControlsMenu = false;
                    background.setColor(sf::Color(255, 255, 255, 255)); // Revert darkening the background
                }
            }
            isEscapeHeld = isEscapePressed;
        }
        if (isInMenu) {
            mainMenu();
        }
        else if (isInControlsMenu) {
            controlsMenu();
        }
        else {
            update();
        }
        render();
        debug();
    }
}
void Game::debug() {
    /*std::cout << "Player position : ( " << player->getPlayer().getPosition().x << ", " << player->getPlayer().getPosition().y << " )" << std::endl;
    std::cout << "HUD position : ( " << hud->getHud().getPosition().x << ", " << hud->getHud().getPosition().y << " )" << std::endl;
    std::cout << "Interact button position : ( " << player->getInteractButton().getPosition().x << ", " << player->getInteractButton().getPosition().y << " )" << std::endl;*/

}
