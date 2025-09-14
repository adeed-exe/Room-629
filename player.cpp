#include "pch.h"
#include "player.h"
#include "game.h"

void Player::initPlayer() {
    frameTimer = 0.f;

    // Frame index and row values for each animation type
    idleX = 0; totalIdle = 8;
    walkX = 0; totalWalk = 8;
    runX = 0; totalRun = 8;
    jumpX = 0; totalJump = 5;

    // Load sprite sheet
    if (idleTexture.loadFromFile("Assets/Sprites/idle_8.png")) {
        std::cout << "Player texture [IDLE_8] loaded!" << std::endl;
    }
    if (walkTexture.loadFromFile("Assets/Sprites/walk_8.png")) {
        std::cout << "Player texture [WALK_8] loaded!" << std::endl;
    }
    if (runTexture.loadFromFile("Assets/Sprites/run_8.png")) {
        std::cout << "Player texture [RUN_8] loaded!" << std::endl;
    }
    if (jumpTexture.loadFromFile("Assets/Sprites/jump_9.png")) {
        std::cout << "Player texture [JUMP_9] loaded!" << std::endl;
    }

    playerChar.setTexture(playerTexture, true);
    playerChar.setTextureRect(sf::IntRect({ idleX * game->frameWidth, 0 }, { game->frameWidth, game->frameHeight }));
    playerChar.setScale({ game->scale, game->scale });
    playerChar.setOrigin({ game->frameWidth / 2.f, game->frameHeight / 2.f });
    playerChar.setPosition({ 1920 / 2, game->ground });
}

Player::Player(Game* gamePtr) : game(gamePtr), playerChar(playerTexture) {
    initPlayer();
}

void Player::animateIdle() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTexture(idleTexture);
        playerChar.setTextureRect(sf::IntRect({ idleX * game->frameWidth, 0 }, { game->frameWidth, game->frameHeight }));
        playerChar.setOrigin({ game->frameWidth / 2.f, game->frameHeight / 2.f });
        idleX = (idleX + 1) % totalIdle;
    }
}

void Player::animateWalk() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTexture(walkTexture);
        playerChar.setTextureRect(sf::IntRect({ walkX * game->frameWidth, 0 }, { game->frameWidth, game->frameHeight }));
        playerChar.setOrigin({ game->frameWidth / 2.f, game->frameHeight / 2.f });
        walkX = (walkX + 1) % totalWalk;
    }
}

void Player::animateRun() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTexture(runTexture);
        playerChar.setTextureRect(sf::IntRect({ runX * game->frameWidth, 0 }, { game->frameWidth, game->frameHeight }));
        playerChar.setOrigin({ game->frameWidth / 2.f, game->frameHeight / 2.f });
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
        playerChar.setTexture(jumpTexture);
        playerChar.setTextureRect(sf::IntRect({ jumpX * game->frameWidth, 0 * game->frameHeight }, { game->frameWidth, game->frameHeight }));
        jumpX++;
    }
}

sf::Sprite& Player::getPlayer() 
{ 
    return playerChar; 
}