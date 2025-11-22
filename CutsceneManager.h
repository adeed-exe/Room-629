#pragma once
#include "PCH.h"
#include "game.h"

class Game;

class CutsceneSir {
private:
    Game* game; // Pointer to the main game instance

    // Textures for the sir
    sf::Texture sirTexture;

    float frameTimer;
    int idleX, totalIdle;
    int frameWidth, frameHeight;
    float scale;
    sf::Vector2f pos;

    void initSir();

public:
    sf::Sprite sir;

    CutsceneSir(Game* gamePtr);
    void animateIdle();
    sf::Sprite& getSir();
};

class CutsceneAction {
public:
    virtual ~CutsceneAction() = default;
    virtual bool update(float dt, Game* game) = 0;
    // return true = action finished
};

class WaitAction : public CutsceneAction {
private:
    float timeLeft;

public:
    WaitAction(float duration) : timeLeft(duration) {}

    bool update(float dt, Game* game) override {
        timeLeft -= dt;
        return timeLeft <= 0.f;
    }
};

class MoveAction : public CutsceneAction {
private:
    float timeLeft;
    sf::Vector2f velocity;
    float scale = 4.f;

public:
    MoveAction(float duration, sf::Vector2f vel)
        : timeLeft(duration), velocity(vel) {
    }

    bool update(float dt, Game* game) override;
};

class DialogueAction : public CutsceneAction {
private:
    std::string text;
    bool shown = false;
public:
    DialogueAction(const std::string& t) : text(t) {}
    bool update(float dt, Game* game) override;
};


class EndCutsceneAction : public CutsceneAction {
public:
    bool update(float dt, Game* game) override;
};

class CutsceneManager {
private:
    std::queue<CutsceneAction*> actions;
    bool running = false;

public:
    void start();
    void addAction(CutsceneAction* action);
    void update(float dt, Game* game);
    bool isRunning() const { return running; }
};
