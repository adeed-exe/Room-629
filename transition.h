#pragma once

#include "PCH.h"

class Transition {
private:
    sf::RectangleShape fadeRect;
    float alpha;
    bool isTransitioning;
    bool fadeOut;       // Fading to black if true, fading back if false
    bool pauseAtBlack;  // Whether we're holding the full-black pause
    float pauseCounter;
    float pauseDuration;

    // Stored callback executed once when full-black achieved.
    std::function<void()> onFullBlackCallback;

public:
    explicit Transition(float pauseTime = 0.8f);

    // Start a transition; onFullBlack is called once when screen becomes fully black.
    void start(std::function<void()> onFullBlack = nullptr);

    // Immediately reset/clear the transition state.
    void reset();

    // Call every frame.
    void update(float deltaTime);

    // Draw the fade rect (call during render).
    void render(sf::RenderWindow& window);

    bool getIsTransitioning() const { return isTransitioning; }
};