#include "pch.h"
#include "player.h"
#include "game.h"

void Player::initPlayer() {
    frameTimer = 0.f;

    // Frame index and row values for each animation type
    idleX = 0; idleY = 0; totalIdle = 7;
    walkX = 0; walkY = 1; totalWalk = 6;
    runX = 0; runY = 2; totalRun = 6;
    jumpX = 0; jumpY = 3; totalJump = 4;
    crouchX = 0; crouchY = 4; totalCrouch = 6;
    fallX = 0; fallY = 5; totalFall = 7;

    // Load sprite sheet
    if (playerTexture.loadFromFile("Assets/Sprites/char_spritesheet.png")) {
        std::cout << "Player texture loaded!" << std::endl;
    }
    playerChar.setTexture(playerTexture, true);
    playerChar.setTextureRect(sf::IntRect({ idleX * game->frameWidth, idleY * game->frameHeight }, { game->frameWidth, game->frameHeight }));
    playerChar.setScale({ game->scale + 2.f, game->scale + 2.f });
    playerChar.setOrigin({ 0, 0 });
    playerChar.setPosition({ 1920/2, game->ground });
}

Player::Player(Game* gamePtr) : game(gamePtr), playerChar(playerTexture) {
    initPlayer();
}

void Player::animateIdle() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTextureRect(sf::IntRect({ idleX * game->frameWidth, idleY * game->frameHeight }, { game->frameWidth, game->frameHeight }));
        idleX = (idleX + 1) % totalIdle;
    }
}

void Player::animateWalk() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTextureRect(sf::IntRect({ walkX * game->frameWidth, walkY * game->frameHeight }, { game->frameWidth, game->frameHeight }));
        walkX = (walkX + 1) % totalWalk;
    }
}

void Player::animateRun() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTextureRect(sf::IntRect({ runX * game->frameWidth, runY * game->frameHeight }, { game->frameWidth, game->frameHeight }));
        runX = (runX + 1) % totalRun;
    }
}

void Player::animateJump() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        if (jumpX >= totalJump) {
            game->playerJumping = false;
            jumpX = 0;
            return;
        }
        playerChar.setTextureRect(sf::IntRect({ jumpX * game->frameWidth, jumpY * game->frameHeight }, { game->frameWidth, game->frameHeight }));
        jumpX++;
    }
}

void Player::animateCrouch() {
    if (game->playerVelocity.x) {
        frameTimer += game->deltaTime;
        if (frameTimer >= game->animationSpeed) {
            frameTimer = 0.f;
            playerChar.setTextureRect(sf::IntRect({ crouchX * game->frameWidth, crouchY * game->frameHeight }, { game->frameWidth, game->frameHeight }));
            crouchX = (crouchX + 1) % totalCrouch;
        }
    }
    else {
        playerChar.setTextureRect(sf::IntRect({ 1 * game->frameWidth, crouchY * game->frameHeight }, { game->frameWidth, game->frameHeight }));
    }
}

void Player::animateFall() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTextureRect(sf::IntRect({ fallX * game->frameWidth, fallY * game->frameHeight }, { game->frameWidth, game->frameHeight }));
        fallX = (fallX + 1) % totalFall;
    }
}

sf::Sprite& Player::getPlayer() { return playerChar; };