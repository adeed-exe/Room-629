#include "pch.h"
#include "player.h"
#include "game.h"

void player::initPlayer() {
    frameTimer = 0.f;

    idleX = 0, idleY = 0, totalIdle = 10;
    runX = 0, runY = 1, totalRun = 8;
    jumpX = 0, jumpY = 2, totalJump = 3;

    if (playerTexture.loadFromFile("Assets/Sprites/char_spritesheet.png")) {
        std::cout << "Player texture loaded!" << std::endl;
    }
    playerChar.setTexture(playerTexture, true);
    playerChar.setScale({ g->scale, g->scale });
    playerChar.setOrigin({ 0, 0 });
    playerChar.setPosition({ 840, g->ground });
}

player::player(game* gamePtr) : g(gamePtr), playerChar(playerTexture) {
    initPlayer();
}

sf::Sprite& player::getSprite() {
    return playerChar;
}

void player::animateIdle() {
    frameTimer += g->dt;
    if (frameTimer >= g->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTextureRect(
            sf::IntRect({ idleX * g->frameWidth, idleY * g->frameHeight },
                { g->frameWidth, g->frameHeight }));
        idleX = (idleX + 1) % totalIdle;
    }
}

void player::animateRun() {
    frameTimer += g->dt;
    if (frameTimer >= g->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTextureRect(
            sf::IntRect({ runX * g->frameWidth, runY * g->frameHeight },
                { g->frameWidth, g->frameHeight }));
        runX = (runX + 1) % totalRun;
    }
}

void player::animateJump() {
    frameTimer += g->dt;
    if (frameTimer >= g->animationSpeed) {
        frameTimer = 0.f;
        if (jumpX >= totalJump) {
            g->playerJumping = 0;
            jumpX = 0;
            return;
        }
        playerChar.setTextureRect(
            sf::IntRect({ jumpX * g->frameWidth, jumpY * g->frameHeight },
                { g->frameWidth, g->frameHeight }));
        jumpX++;
    }
}