#include "PCH.h"
#include "Game.h"
#include "Nightmare.h"

void Nightmare::initNightmare() {
    frameTimer = 0.f;

    // Frame index and row values for each animation type
    idleX = 0, idleY = 0, totalIdle = 7;
    walkX = 0, walkY = 1, totalWalk = 7;
    runX = 0, runY = 2, totalRun = 7;
    attackX = 0, attackY = 3, totalAttack = 7;

    frameWidth = 48;
    frameHeight = 48;

    // Load sprite sheet
    if (nightmareTexture.loadFromFile("Assets/Sprites/nightmare_spritesheet.png")) {
        std::cout << "Nightmare texture loaded!" << std::endl;
    }

    nightmareChar.setTexture(nightmareTexture, true);
    nightmareChar.setTextureRect(sf::IntRect({ idleX * frameWidth, 0 }, { frameWidth, frameHeight }));
    nightmareChar.setScale({ -2 * game->scale, 2 * game->scale });
    nightmareChar.setOrigin({ frameWidth / 2.f, frameHeight / 2.f });
    nightmareChar.setPosition({ game->player->getPlayer().getPosition().x - 200, game->ground + 22});
}

Nightmare::Nightmare(Game* gamePtr) : game(gamePtr), nightmareChar(nightmareTexture) {
	initNightmare();
}

void Nightmare::animateIdle() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        nightmareChar.setTextureRect(sf::IntRect({ idleX * frameWidth, idleY * frameHeight }, { frameWidth, frameHeight }));
        idleX = (idleX + 1) % totalIdle;
    }
}

void Nightmare::animateWalk() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        nightmareChar.setTextureRect(sf::IntRect({ walkX * frameWidth, walkY * frameHeight }, { frameWidth, frameHeight }));
        walkX = (walkX + 1) % totalWalk;
        if (walkX == 2 || walkX == 6) {
            game->soundSystem->playFootstepSound(0.5f);
        }
    }
}

void Nightmare::animateRun() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        nightmareChar.setTextureRect(sf::IntRect({ runX * frameWidth, runY * frameHeight }, { frameWidth, frameHeight }));
        runX = (runX + 1) % totalRun;
        if (runX == 2 || runX == 6) {
            game->soundSystem->playFootstepSound(1.f);
        }
    }
}

void Nightmare::animateAttack() {
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        nightmareChar.setTextureRect(sf::IntRect({ attackX * frameWidth, attackY * frameHeight }, { frameWidth, frameHeight }));
        attackX = (attackX + 1) % totalAttack;
    }
}

sf::Sprite& Nightmare::getNightmare() {
    return nightmareChar;
}