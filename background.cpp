#include "pch.h"
#include "background.h"
#include "game.h"

void Background::initBackground() {
    // Load background layers
    if (backgroundTexture1.loadFromFile("Assets/Sprites/bg1.png")) {
        std::cout << "Background texture 1 loaded!" << std::endl;
    }
    background1.setTexture(backgroundTexture1, true);
    background1.setScale({ game->scale, game->scale });
    background1.setPosition({ 0, 0 });

    if (backgroundTexture2.loadFromFile("Assets/Sprites/bg2.png")) {
        std::cout << "Background texture 2 loaded!" << std::endl;
    }
    background2.setTexture(backgroundTexture2, true);
    background2.setScale({ game->scale, game->scale });
    background2.setPosition({ -960, -120 });

    if (backgroundTexture3.loadFromFile("Assets/Sprites/bg3.png")) {
        std::cout << "Background texture 3 loaded!" << std::endl;
    }
    background3.setTexture(backgroundTexture3, true);
    background3.setScale({ game->scale, game->scale });
    background3.setPosition({ -960, -120 });

    if (backgroundTexture4.loadFromFile("Assets/Sprites/bg4.png")) {
        std::cout << "Background texture 4 loaded!" << std::endl;
    }
    background4.setTexture(backgroundTexture4, true);
    background4.setScale({ game->scale, game->scale });
    background4.setPosition({ -960, -120 });
}

Background::Background(Game* gamePtr) : game(gamePtr),
background1(backgroundTexture1), background2(backgroundTexture2),
background3(backgroundTexture3), background4(backgroundTexture4) {
    initBackground();
}

void Background::moveLeft() {
    game->playerVelocity.x += game->playerMoveSpeed;
}

void Background::moveRight() {
    game->playerVelocity.x -= game->playerMoveSpeed;
}

void Background::jump() {
    game->playerInAir = 1;
    game->playerJumping = 1;
    game->playerVelocity.y = game->playerMoveSpeed + 50.f;
}

sf::Sprite& Background::getBackground1() { return background1; }
sf::Sprite& Background::getBackground2() { return background2; }
sf::Sprite& Background::getBackground3() { return background3; }
sf::Sprite& Background::getBackground4() { return background4; }