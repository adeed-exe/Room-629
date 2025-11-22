#include "PCH.h"
#include "CutsceneManager.h"

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
