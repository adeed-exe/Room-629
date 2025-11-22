#include "PCH.h"
#include "CutsceneManager.h"


//-----Sir Animation Sprite ------

void CutsceneSir::initSir() {
    frameTimer = 0.f;

    idleX = 0; totalIdle = 8;

    frameWidth = 43;
    frameHeight = 43;
    scale = game->scale;
    pos = game->sirPos;

    if (sirTexture.loadFromFile("Assets/Sprites/sir_idle_8.png")) {
        std::cout << "Player texture [SIR_IDLE_8] loaded!" << std::endl;
    }

    sir.setTextureRect(sf::IntRect({ idleX * frameWidth, 0 }, { frameWidth, frameHeight }));
    sir.setScale({ -scale, scale });
    sir.setOrigin({ frameWidth / 2.f, frameHeight / 2.f });
    sir.setPosition(pos);
}

void CutsceneSir::animateIdle() {
    pos = game->sirPos;
    frameTimer += game->deltaTime;
    if (frameTimer >= game->animationSpeed) {
        frameTimer = 0.f;
        sir.setTexture(sirTexture);
        sir.setTextureRect(sf::IntRect({ idleX * frameWidth, 0 }, { frameWidth, frameHeight }));
        idleX = (idleX + 1) % totalIdle;
        sir.setPosition(pos);
    }
}

CutsceneSir::CutsceneSir(Game* gamePtr) : game(gamePtr), sir(sirTexture)
{
    initSir();
}

sf::Sprite& CutsceneSir::getSir() {
    return sir;
}

//Cutscene Creator
void CutsceneManager::start() {
    running = true;
}

void CutsceneManager::addAction(CutsceneAction* action) {
    actions.push(action);
}

void CutsceneManager::update(float dt, Game* game) {
    if (!running || actions.empty()) return;

    CutsceneAction* current = actions.front();

    if (current->update(dt, game)) {

        game->playerVelocity = { 0.f, 0.f };

        delete current;
        actions.pop();

        if (actions.empty())
            running = false;
    }
}




//bool MoveAction::update(float dt, Game* game) {
//    timeLeft -= dt;
//
//    // Force player movement during cutscene
//    game->playerVelocity.x += velocity.x;
//
//    return timeLeft <= 0.f;
//}

bool MoveAction::update(float dt, Game* game) {
    timeLeft -= dt;

    // Set player velocity directly while this action is active
    if(velocity.x < 0) 
        game->player->getPlayer().setScale({ -scale, scale });
    else if (velocity.x > 0)
        game->player->getPlayer().setScale({ scale, scale });

    game->playerVelocity.x = velocity.x;
    game->playerVelocity.y = velocity.y;

    if (timeLeft <= 0.f) {
        // Action finished: reset velocity so player stops moving
        game->playerVelocity.x = 0.f;
        game->playerVelocity.y = 0.f;
        return true;
    }

    return false;
}


bool EndCutsceneAction::update(float dt, Game* game) {
    game->endCutscene();
    game->enablePlayerInput();
    return true;
}


bool DialogueAction::update(float dt, Game* game)
{
    return false;
}
