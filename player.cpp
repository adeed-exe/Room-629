#include "PCH.h"
#include "Player.h"
#include "Game.h"

void Player::initPlayer() {
    frameTimer = 0.f;

    // Frame index and row values for each animation type
    idleX = 0; totalIdle = 8;
    walkX = 0; totalWalk = 8;
    runX = 0; totalRun = 8;
    jumpX = 0; totalJump = 5;

    frameWidth = 43;
    frameHeight = 43;

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

    if (interactButtonTexture.loadFromFile("Assets/Sprites/button_interact.png")) {
        std::cout << "F button texture loaded!" << std::endl;
    }

    playerChar.setTextureRect(sf::IntRect({ idleX * frameWidth, 0 }, { frameWidth, frameHeight }));
    playerChar.setScale({ game->scale, game->scale });
    playerChar.setOrigin({ frameWidth / 2.f, frameHeight / 2.f });
    playerChar.setPosition({ 1920 / 2, game->ground });

    interactButton.setTexture(interactButtonTexture, true);
    interactButton.setOrigin(interactButton.getGlobalBounds().size / 2.f);
}

Player::Player(Game* gamePtr) : game(gamePtr), playerChar(playerTexture), interactButton(interactButtonTexture) {
    initPlayer();
}

void Player::animateIdle() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTexture(idleTexture);
        playerChar.setTextureRect(sf::IntRect({ idleX * frameWidth, 0 }, { frameWidth, frameHeight }));
        idleX = (idleX + 1) % totalIdle;
    }
}

void Player::animateWalk() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTexture(walkTexture);
        playerChar.setTextureRect(sf::IntRect({ walkX * frameWidth, 0 }, { frameWidth, frameHeight }));
        walkX = (walkX + 1) % totalWalk;
        if (walkX == 2 || walkX == 6) {
            game->soundSystem->playFootstepSound(0.5f);
        }
    }
}

void Player::animateRun() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        playerChar.setTexture(runTexture);
        playerChar.setTextureRect(sf::IntRect({ runX * frameWidth, 0 }, { frameWidth, frameHeight }));
        runX = (runX + 1) % totalRun;
        if (runX == 2 || runX == 6) {
            game->soundSystem->playFootstepSound(1.f);
        }
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
        playerChar.setTextureRect(sf::IntRect({ jumpX * frameWidth, 0 }, { frameWidth, frameHeight }));
        jumpX++;
    }
}

sf::Sprite& Player::getPlayer() { 
    return playerChar; 
}

sf::Sprite& Player::getInteractButton() {
    return interactButton;
}
