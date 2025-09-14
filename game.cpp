#include "pch.h"
#include "game.h"

// Private
void Game::initVariables() {
    window = nullptr;

    frameWidth = 43;
    frameHeight = 43;
    scale = 4.f;
    animationSpeed = 0.08f;
    playerMoveSpeed = 150.f;
    gravity = 880.f;
    ground = 180.f;

    isInMenu = true;
    isInControlsMenu = false;
    isMouseHeld = false;

    playerVelocity = { 0.f, 0.f };
    playerInAir = false;
    playerJumping = false;
    playerRunning = false;
    playerCrouching = false;
    isCrouchHeld = false;
    isEscapeHeld = false;

    if (backgroundTexture.loadFromFile("Assets/Sprites/Room629_BG_01.png")) {
        std::cout << "Background texture loaded!" << std::endl;
    }
    background.setTexture(backgroundTexture, true);
    //background.setScale({ 1920 / 1920.f, 960 / 300.f });
    background.setColor(sf::Color(255, 255, 255, 125));
    background.setOrigin(background.getLocalBounds().size / 2.f);

    //now set to the top of the screen for easier calculation
    background.setPosition({ 960.f, 150.f});
}

void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "Room 629", sf::Style::None);
    window->setVerticalSyncEnabled(true);
}

void Game::initViewSystem() {
    viewSystem = new ViewSystem( 1920.f, 300.f, 1920.f, 300.f);
}

// Public
Game::Game() : background(backgroundTexture) {
    initVariables();
    initWindow();
    initViewSystem();
    player = new Player(this);
    menu = new Menu(this);
    mainMenuText = menu->getMainMenuText();
    controlsMenuText = menu->getControlsMenuText();
}

Game::~Game() {
    delete player;
    delete menu;
    delete window;
    delete viewSystem;
}

void Game::mainMenu() {
    sf::Vector2f mousePos(sf::Mouse::getPosition(*window));
    for (int i = 0; i < mainMenuText.size(); i++) {
        if (mainMenuText[i].getGlobalBounds().contains(mousePos)) {
            mainMenuText[i].setFillColor(sf::Color(150, 150, 150)); // Darken button while hovering

            int isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
            if (isMousePressed && !isMouseHeld) {
                if (i == 0) {
                    // Pressing continue button
                    isInMenu = false;
                    background.setColor(sf::Color(255, 255, 255, 255)); // Reset background darkening
                }
                else if (i == 2) {
                    // Pressing controls button
                    isInControlsMenu = true;
                    isInMenu = false;
                }
                else if (i == 3) {
                    // Pressing exit button
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
            // Pressing back button
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
    // Toggle run
    playerRunning = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && !playerCrouching;

    float moveSpeed = playerMoveSpeed;

    if (playerRunning) {
        moveSpeed *= 2.0f; // Increase speed while running
    }

    // Move left and right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && player->getPlayer().getPosition().x >= 60) {
        player->getPlayer().setScale({ -scale, scale });
        playerVelocity.x -= moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && player->getPlayer().getPosition().x <= 1860) {
        player->getPlayer().setScale({ scale, scale });
        playerVelocity.x += moveSpeed;
    }

    // Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !playerInAir) {
        playerInAir = true;
        playerJumping = true;
        playerVelocity.y = -(playerMoveSpeed + 100.f);
    }
}

void Game::updatePlayer() {
    // Animate depending on state
    if (playerJumping) {
        player->animateJump();
    }
    else if (playerVelocity.x && playerRunning) {
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

    inputHandler();

    if (playerInAir) {
        playerVelocity.y += gravity * deltaTime;
    }

    player->getPlayer().move(playerVelocity * deltaTime);

    updatePlayer();

    viewSystem->update(player->getPlayer().getPosition());
}

void Game::render() {
    window->clear();

    window->draw(background); // Draws the entire BackGround

    // -------- IN GAME ---------
    if (!isInMenu && !isInControlsMenu) {
        window->setView(viewSystem->getView()); // A view of a portion of the background
        window->draw(player->getPlayer());
    }

    // ------ MAINMENU UI ---------
    else {
        window->setView(window->getDefaultView()); // Setting the view back to the entire screen
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
    std::cout << "Player position : ( " << player->getPlayer().getPosition().x << ", " << player->getPlayer().getPosition().y << " )" << std::endl;
}
