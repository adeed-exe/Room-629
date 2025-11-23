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

    // Store the specific speeds/duration for the *current* transition
    float currentFadeOutSpeed;
    float currentFadeInSpeed;
    float currentPauseDuration;

    // Stored callback executed once when full-black achieved.
    std::function<void()> onFullBlackCallback;

public:
    // Change constructor back to taking default values
    explicit Transition(float defaultFadeOutSpd = 400.f, float defaultFadeInSpd = 500.f, float defaultPauseTime = 0.8f);

    // Update the start function to accept custom speeds for THIS transition event
    void start(std::function<void()> onFullBlack = nullptr, float fadeOutSpd = 0.f, float fadeInSpd = 0.f, float pauseTime = 0.f);

    // Immediately reset/clear the transition state.
    void reset();

    // Call every frame.
    void update(float deltaTime);

    // Draw the fade rect (call during render).
    void render(sf::RenderWindow& window);

    bool getIsTransitioning() const { return isTransitioning; }
};
