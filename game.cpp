#include "pch.h"
#include "game.h"

void Game::initVariables() {
    window = nullptr;

    frameWidth = 48;
    frameHeight = 48;
    scale = 10.f;
    animationSpeed = 0.1f;
    playerMoveSpeed = 150.f;
    gravity = 880.f;
    ground = 482.f;

    isInMenu = true;
    isInControlsMenu = false;
    isMouseHeld = false;

    playerVelocity = { 0.f, 0.f };
    playerInAir = false;
    playerJumping = false;
    playerRunning = false;
    playerCrouching = false;
    isCrouchHeld = false;

    if (backgroundTexture.loadFromFile("Assets/Sprites/classroomBg.png")) {
        std::cout << "Background texture loaded!" << std::endl;
    }
    background.setTexture(backgroundTexture, true);
    background.setScale({ 1920 / 1300.f, 1920 / 1300.f });
    background.setColor(sf::Color(255, 255, 255, 125));
    background.setOrigin(background.getLocalBounds().size / 2.f);
    background.setPosition({ 960, 540 });
}

void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "Room 629", sf::Style::None);
    window->setFramerateLimit(120);
}

Game::Game() : background(backgroundTexture) {
    initVariables();
    initWindow();
    player = new Player(this);
    menu = new Menu(this);
    mainMenuText = menu->getMainMenuText();
    controlsMenuText = menu->getControlsMenuText();
}

Game::~Game() {
    delete player;
    delete menu;
    delete window;
}

void Game::mainMenu() {
    sf::Vector2f mousePos(sf::Mouse::getPosition(*window));
    for (int i = 0; i < mainMenuText.size(); i++) {
        if (mainMenuText[i].getGlobalBounds().contains(mousePos)) {
            mainMenuText[i].setFillColor(sf::Color(200, 200, 200)); // Darken button while hovering

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
    if (controlsMenuText[3].getGlobalBounds().contains(mousePos)) {
        controlsMenuText[3].setFillColor(sf::Color(200, 200, 200)); // Darken button while hovering

        int isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (isMousePressed && !isMouseHeld) {
            // Pressing back button
            isInMenu = true;
            isInControlsMenu = false;
        }
        isMouseHeld = isMousePressed;
    }
    else {
        controlsMenuText[3].setFillColor(sf::Color(255, 255, 255));
    }
}

void Game::inputHandler() {
    // Toggle run
    playerRunning = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && !playerCrouching;

    // Toggle crouch
    int isCrouchPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
    if (isCrouchPressed && !isCrouchHeld) {
        if (playerCrouching) {
            playerCrouching = false;
        }
        else {
            playerCrouching = true;
        }
    }
    isCrouchHeld = isCrouchPressed;

    float moveSpeed = playerMoveSpeed;

    if (playerRunning) {
        moveSpeed *= 1.5f; // Increase speed while running
    }

    if (playerCrouching) {
        moveSpeed *= 0.5f; // Decrease speed while crouching
    }

    // Move left and right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        player->getPlayer().setScale({ -scale - 2.f, scale + 2.f });
        player->getPlayer().setOrigin({ static_cast<float>(frameWidth), 0 });
        playerVelocity.x -= moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        player->getPlayer().setScale({ scale + 2.f, scale + 2.f });
        player->getPlayer().setOrigin({ 0, 0 });
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
    else if (playerCrouching) {
        player->animateCrouch();
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
    if (deltaTime > 1.f / 120.f) {
        deltaTime = 1.f / 120.f; // Clamp to avoid large jumps at low framerates
    }

    playerVelocity.x = 0;
    playerRunning = false;

    // Clamp player to ground
    if (player->getPlayer().getPosition().y > ground) {
        playerInAir = false;
        player->getPlayer().setPosition({ player->getPlayer().getPosition().x, ground });
    }

    inputHandler();

    if (playerInAir) {
        playerVelocity.y += gravity * deltaTime;
    }

    player->getPlayer().move(playerVelocity * deltaTime);

    updatePlayer();
}

void Game::render() {
    window->clear();

    window->draw(background);

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
    else {
        window->draw(player->getPlayer());
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && !isInMenu && !isInControlsMenu) {
                isInMenu = true;
                background.setColor(sf::Color(255, 255, 255, 125)); // Darken background while in menu
            }
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
    }
}