#include "pch.h"
#include "game.h"

void Game::initVariables() {
    window = nullptr;

    frameWidth = 48, frameHeight = 48;
    scale = 5.f, animationSpeed = 0.1f;
    playerMoveSpeed = 175.f, gravity = 980.f;
    ground = 780.f, frameTimer = 0.f;

    playerRunning = 0, playerFell = 0;
    playerCrouching = 0, isCrouchHeld = 0;
    playerJumping = 0, playerInAir = 0;
    playerVelocity.x = 0.f, playerVelocity.y = 0.f;
}

void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "Room 629", sf::Style::None);
    window->setFramerateLimit(60);
    window->setMouseCursorVisible(false);
}

Game::Game() {
    initVariables();
    initWindow();
    player = new Player(this);
    background = new Background(this);
}

Game::~Game() {
    delete window;
}

const bool Game::running() const {
    return window->isOpen();
}

void Game::pollEvents() {
    while (const std::optional event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window->close();
        }
    }
}

void Game::resetPlayer() {
    playerVelocity.x = 0.f;
    playerRunning = 0;

    if (playerInAir) {
        playerVelocity.y -= gravity * deltaTime;
    }
}

void Game::updatePlayer() {
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

void Game::resetBackground() {
    if (background->getBackground2().getPosition().y < -120) {
        playerInAir = 0;
        background->getBackground2().setPosition({ background->getBackground2().getPosition().x, -120.f });
    }
    if (background->getBackground2().getPosition().x >= 0) {
        background->getBackground2().setPosition({ background->getBackground2().getPosition().x - 1920, background->getBackground2().getPosition().y });
    }
    if (background->getBackground2().getPosition().x <= -1920) {
        background->getBackground2().setPosition({ background->getBackground2().getPosition().x + 1920, background->getBackground2().getPosition().y });
    }

    if (background->getBackground3().getPosition().y < -120) {
        playerInAir = 0;
        background->getBackground3().setPosition({ background->getBackground3().getPosition().x, -120.f });
    }
    if (background->getBackground3().getPosition().x >= 0) {
        background->getBackground3().setPosition({ background->getBackground3().getPosition().x - 1920, background->getBackground3().getPosition().y });
    }
    if (background->getBackground3().getPosition().x <= -1920) {
        background->getBackground3().setPosition({ background->getBackground3().getPosition().x + 1920, background->getBackground3().getPosition().y });
    }

    if (background->getBackground4().getPosition().y < -120) {
        playerInAir = 0;
        background->getBackground4().setPosition({ background->getBackground4().getPosition().x, -120.f });
    }
    if (background->getBackground4().getPosition().x >= 0) {
        background->getBackground4().setPosition({ background->getBackground4().getPosition().x - 1920, background->getBackground4().getPosition().y });
    }
    if (background->getBackground4().getPosition().x <= -1920) {
        background->getBackground4().setPosition({ background->getBackground4().getPosition().x + 1920, background->getBackground4().getPosition().y });
    }
}

void Game::updateBackground() {
    background->getBackground2().move(playerVelocity * deltaTime * 0.25f);
    background->getBackground3().move(playerVelocity * deltaTime * 0.50f);
    background->getBackground4().move(playerVelocity * deltaTime * 0.75f);
}

void Game::movementHandler() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        player->getSprite().setScale({ -scale, scale });
        player->getSprite().setOrigin({ static_cast<float>(frameWidth), 0 });
        background->moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        player->getSprite().setScale({ scale, scale });
        player->getSprite().setOrigin({ 0, 0 });
        background->moveRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !playerInAir) {
        background->jump();
    }
    int isCrouchPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C);
    if (isCrouchPressed && !isCrouchHeld) {
        playerCrouching ^= 1;
    }
    isCrouchHeld = isCrouchPressed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && !playerCrouching) {
        playerRunning = 1;
    }
}

void Game::update() {
    deltaTime = clock.restart().asSeconds();

    pollEvents();

    resetPlayer();
    resetBackground();

    movementHandler();

    updatePlayer();
    updateBackground();
}

void Game::render() {
    window->clear();

    window->draw(background->getBackground1());
    window->draw(background->getBackground2());
    window->draw(background->getBackground3());
    window->draw(background->getBackground4());
    window->draw(player->getSprite());

    window->display();
}