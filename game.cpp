#include "pch.h"
#include "game.h"

void Game::initVariables() {
    window = nullptr;

    frameWidth = 48;
    frameHeight = 48;
    scale = 5.f;
    animationSpeed = 0.1f;
    playerMoveSpeed = 250.f;
    gravity = 880.f;
    ground = 684.f;

    playerVelocity = { 0.f, 0.f };
    playerInAir = false;
    playerJumping = false;
    playerRunning = false;
    playerCrouching = false;
    isCrouchHeld = false;
}

void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "Room 629", sf::Style::None);
    window->setFramerateLimit(120);
}

Game::Game() {
    initVariables();
    initWindow();
    background = new Background(this);
    player = new Player(this);
    backgrounds.push_back(background->getBackground1());
    backgrounds.push_back(background->getBackground2());
    backgrounds.push_back(background->getBackground3());
    backgrounds.push_back(background->getBackground4());
}

Game::~Game() {
    delete player;
    delete background;
    delete window;
}

void Game::resetBackground() {
    for (int i = 1; i < 4; i++) {
        if (backgrounds[i].getPosition().y <= -120) {
            playerInAir = false;
            backgrounds[i].setPosition({ backgrounds[i].getPosition().x, -120.f });
        }
        if (backgrounds[i].getPosition().x >= 0) {
            backgrounds[i].setPosition({ backgrounds[i].getPosition().x - 1920, backgrounds[i].getPosition().y });
        }
        if (backgrounds[i].getPosition().x <= -1920) {
            backgrounds[i].setPosition({ backgrounds[i].getPosition().x + 1920, backgrounds[i].getPosition().y });
        }
    }
}

void Game::inputHandler() {
    float moveSpeed = playerMoveSpeed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && !playerCrouching)
        moveSpeed *= 1.5f; // Increase speed while running

    if (playerCrouching)
        moveSpeed *= 0.5f; // Decrease speed while crouching

    // Reset horizontal velocity
    playerVelocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        player->getPlayer().setScale({ -scale - 3.f, scale + 3.f });
        player->getPlayer().setOrigin({ static_cast<float>(frameWidth), 0 });
        playerVelocity.x += moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        player->getPlayer().setScale({ scale + 3.f, scale + 3.f });
        player->getPlayer().setOrigin({ 0, 0 });
        playerVelocity.x -= moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !playerInAir) {
        background->jump();
    }

    int isCrouchPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C);
    if (isCrouchPressed && !isCrouchHeld) {
        playerCrouching ^= 1;
    }
    isCrouchHeld = isCrouchPressed;

    playerRunning = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && !playerCrouching;
}

void Game::updateBackground() {
    // Move background layers at different speeds
    if (playerInAir)
        playerVelocity.y -= gravity * deltaTime;
    for (int i = 1; i < 4; i++) {
        backgrounds[i].move({ playerVelocity * deltaTime * 0.25f * static_cast<float>(i)});
    }
}

void Game::updatePlayer() {
    // Animate depending on state
    if (playerJumping)
        player->animateJump();
    else if (playerCrouching)
        player->animateCrouch();
    else if (playerVelocity.x && playerRunning)
        player->animateRun();
    else if (playerVelocity.x)
        player->animateWalk();
    else
        player->animateIdle();
}

void Game::update() {
    deltaTime = dtClock.restart().asSeconds();
    if (deltaTime > 1.f / 120.f)
        deltaTime = 1.f / 120.f; // Clamp to avoid large jumps

    playerVelocity.x = 0;
    playerRunning = false;

    resetBackground();
    inputHandler();
    updateBackground();
    updatePlayer();
}

void Game::render() {
    window->clear();

    for (auto& bg : backgrounds) {
        window->draw(bg);
    }

    window->draw(player->getPlayer());

    window->display();
}

void Game::run() {
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window->close();
        }
        update();
        render();
    }
}