#include "pch.h"
#include "background.h"
#include "game.h"

void background::initBackground()
{
    if (bg1Texture.loadFromFile("Assets/Sprites/bg1.png")) {
        std::cout << "Background texture 1 loaded!" << std::endl;
    }
    bg1.setTexture(bg1Texture, true);
    bg1.setScale({ g->scale, g->scale });
    bg1.setPosition({ 0, 0 });

    if (bg2Texture.loadFromFile("Assets/Sprites/bg2.png")) {
        std::cout << "Background texture 2 loaded!" << std::endl;
    }
    bg2.setTexture(bg2Texture, true);
    bg2.setScale({ g->scale, g->scale });
    bg2.setPosition({ -960, -120 });

    if (bg3Texture.loadFromFile("Assets/Sprites/bg3.png")) {
        std::cout << "Background texture 3 loaded!" << std::endl;
    }
    bg3.setTexture(bg3Texture, true);
    bg3.setScale({ g->scale, g->scale });
    bg3.setPosition({ -960, -120 });

    if (bg4Texture.loadFromFile("Assets/Sprites/bg4.png")) {
        std::cout << "Background texture 4 loaded!" << std::endl;
    }
    bg4.setTexture(bg4Texture, true);
    bg4.setScale({ g->scale, g->scale });
    bg4.setPosition({ -960, -120 });
}

background::background(game* gamePtr) : g(gamePtr), bg1(bg1Texture), bg2(bg2Texture), bg3(bg3Texture), bg4(bg4Texture) {
    initBackground();
}

sf::Sprite& background::getBg1() {
    return bg1;
}

sf::Sprite& background::getBg2() {
    return bg2;
}

sf::Sprite& background::getBg3() {
    return bg3;
}

sf::Sprite& background::getBg4() {
    return bg4;
}

void background::moveLeft() {
    g->playerVelocity.x += g->playerMoveSpeed;
}

void background::moveRight() {
    g->playerVelocity.x -= g->playerMoveSpeed;
}

void background::jump() {
    g->playerInAir = 1;
    g->playerJumping = 1;
    g->playerVelocity.y = g->playerMoveSpeed;
}