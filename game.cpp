#include "pch.h"
#include "game.h"

void game::initVariables() {
    window = nullptr;

    frameWidth = 48, frameHeight = 48;
    scale = 5.f, animationSpeed = 0.1f;
    playerMoveSpeed = 250.f, gravity = 980.f;
    ground = 700.f, frameTimer = 0.f;

    playerJumping = 0, playerInAir = 0;
    playerVelocity.x = 0.f, playerVelocity.y = 0.f;
}

void game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "Room 629", sf::Style::None);
    window->setFramerateLimit(60);
    window->setMouseCursorVisible(false);
}

game::game() {
    initVariables();
    initWindow();
    p = new player(this);
    bg = new background(this);
}

game::~game() {
    delete window;
}

const bool game::running() const {
    return window->isOpen();
}

void game::pollEvents() {
    while (const std::optional event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window->close();
        }
    }
}

void game::resetPlayer() {
    playerVelocity.x = 0.f;

    if (playerInAir) {
        playerVelocity.y -= gravity * dt;
    }
}

void game::updatePlayer() {
    if (playerVelocity.x && !playerJumping) {
        p->animateRun();
    }
    else if (playerJumping) {
        p->animateJump();
    }
    else {
        p->animateIdle();
    }
}

void game::resetBackground() {
    if (bg->getBg2().getPosition().y < -120) {
        playerInAir = 0;
        bg->getBg2().setPosition({ bg->getBg2().getPosition().x, -120.f });
    }
    if (bg->getBg2().getPosition().x >= 0) {
        bg->getBg2().setPosition({ bg->getBg2().getPosition().x - 1920, bg->getBg2().getPosition().y });
    }
    if (bg->getBg2().getPosition().x <= -1920) {
        bg->getBg2().setPosition({ bg->getBg2().getPosition().x + 1920, bg->getBg2().getPosition().y });
    }

    if (bg->getBg3().getPosition().y < -120) {
        playerInAir = 0;
        bg->getBg3().setPosition({ bg->getBg3().getPosition().x, -120.f });
    }
    if (bg->getBg3().getPosition().x >= 0) {
        bg->getBg3().setPosition({ bg->getBg3().getPosition().x - 1920, bg->getBg3().getPosition().y });
    }
    if (bg->getBg3().getPosition().x <= -1920) {
        bg->getBg3().setPosition({ bg->getBg3().getPosition().x + 1920, bg->getBg3().getPosition().y });
    }

    if (bg->getBg4().getPosition().y < -120) {
        playerInAir = 0;
        bg->getBg4().setPosition({ bg->getBg4().getPosition().x, -120.f });
    }
    if (bg->getBg4().getPosition().x >= 0) {
        bg->getBg4().setPosition({ bg->getBg4().getPosition().x - 1920, bg->getBg4().getPosition().y });
    }
    if (bg->getBg4().getPosition().x <= -1920) {
        bg->getBg4().setPosition({ bg->getBg4().getPosition().x + 1920, bg->getBg4().getPosition().y });
    }
}

void game::updateBackground() {
    bg->getBg2().move(playerVelocity * dt * 0.25f);
    bg->getBg3().move(playerVelocity * dt * 0.5f);
    bg->getBg4().move(playerVelocity * dt * 0.75f);
}

void game::movementHandler() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        p->getSprite().setScale({ -scale, scale });
        p->getSprite().setOrigin({ static_cast<float>(frameWidth), 0 });
        bg->moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        p->getSprite().setScale({ scale, scale });
        p->getSprite().setOrigin({ 0, 0 });
        bg->moveRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !playerInAir) {
        bg->jump();
    }
}

void game::update() {
    dt = clock.restart().asSeconds();

    pollEvents();

    resetPlayer();
    resetBackground();

    movementHandler();

    updatePlayer();
    updateBackground();
}

void game::render() {
    window->clear();

    window->draw(bg->getBg1());
    window->draw(bg->getBg2());
    window->draw(bg->getBg3());
    window->draw(bg->getBg4());
    window->draw(p->getSprite());

    window->display();
}
