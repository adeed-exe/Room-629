#pragma once
#include "pch.h"

class Game;

class transition
{
private:
    sf::RectangleShape fadeRect;
    float alpha;
    bool isTransitioning;
    bool fadeOut;        // true = fade to black, false = fade back in
    bool pauseAtBlack;   // whether we’re pausing at full black
    float pauseCounter;
    float pauseDuration; // how long to pause at black (seconds)

public:

    transition(float pauseTime = 1.f);

    // Control
    void start();  // start transition
    void reset();  // reset to idle

    // Update + Render
    void update(float deltaTime, std::function<void()> onBlack = nullptr);
    void render(sf::RenderWindow& window);

    // Getters
    bool getIsTransitioning() const { return isTransitioning; }

	
};

