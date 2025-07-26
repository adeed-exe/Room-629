#include "pch.h"
#include "player.h"
#include "game.h"

void Player::initPlayer() {
    frameTimer = 0.f;

    idleX = 0, idleY = 0, totalIdle = 10;
    runX = 0, runY = 1, totalRun = 8;
    jumpX = 0, jumpY = 2, totalJump = 3;

    if (playerTexture.loadFromFile("Assets/Sprites/char_spritesheet.png")) {
        std::cout << "Player texture loaded!" << std::endl;
    }
    playerChar.setTexture(playerTexture, true);
    playerChar.setScale({ game->scale, game->scale });
    playerChar.setOrigin({ 0, 0 });
    playerChar.setPosition({ 840, game->ground });
}

Player::Player(Game* gamePtr) : game(gamePtr), playerChar(playerTexture) {
    initPlayer();
}

sf::Sprite& Player::getSprite() {
    return playerChar;
}

void Player::animateIdle() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTextureRect(
            sf::IntRect({ idleX * game->frameWidth, idleY * game->frameHeight },
                { game->frameWidth, game->frameHeight }));
        idleX = (idleX + 1) % totalIdle;
    }
}

void Player::animateRun() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTextureRect(
            sf::IntRect({ runX * game->frameWidth, runY * game->frameHeight },
                { game->frameWidth, game->frameHeight }));
        runX = (runX + 1) % totalRun;
    }
}

void Player::animateJump() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        if (jumpX >= totalJump) {
            game->playerJumping = 0;
            jumpX = 0;
            return;
        }
        playerChar.setTextureRect(
            sf::IntRect({ jumpX * game->frameWidth, jumpY * game->frameHeight },
                { game->frameWidth, game->frameHeight }));
        jumpX++;
    }
}