#include "PCH.h"
#include "Transition.h"

// Initialize default speeds in the constructor
Transition::Transition(float defaultFadeOutSpd, float defaultFadeInSpd, float defaultPauseTime)
    : alpha(0.f)
    , isTransitioning(false)
    , fadeOut(true)
    , pauseAtBlack(false)
    , pauseCounter(0.f)
    , currentFadeOutSpeed(defaultFadeOutSpd)
    , currentFadeInSpeed(defaultFadeInSpd)
    , currentPauseDuration(defaultPauseTime)
    , onFullBlackCallback(nullptr)
{
    fadeRect.setSize({ 1920.f, 1080.f });
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));
}

void Transition::start(std::function<void()> onFullBlack, float fadeOutSpd, float fadeInSpd, float pauseTime) {
    isTransitioning = true;
    fadeOut = true;
    alpha = 0.f;
    pauseAtBlack = false;
    pauseCounter = 0.f;
    onFullBlackCallback = onFullBlack;

    // Store custom speeds if provided (non-zero), otherwise use defaults set in constructor
    if (fadeOutSpd > 0.f) currentFadeOutSpeed = fadeOutSpd;
    if (fadeInSpd > 0.f) currentFadeInSpeed = fadeInSpd;
    if (pauseTime > 0.f) currentPauseDuration = pauseTime;
}

void Transition::reset() {
    isTransitioning = false;
    fadeOut = true;
    alpha = 0.f;
    pauseAtBlack = false;
    pauseCounter = 0.f;
    onFullBlackCallback = nullptr;
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));
    // Speeds remain at their default or last-used values after reset
}

void Transition::update(float deltaTime) {
    if (!isTransitioning) return;

    if (fadeOut) {
        // Use the stored current speed
        alpha += currentFadeOutSpeed * deltaTime;
        if (alpha >= 255.f) {
            alpha = 255.f;

            if (!pauseAtBlack) {
                // Call stored callback once when fully black
                if (onFullBlackCallback) {
                    onFullBlackCallback();
                }
                pauseAtBlack = true;
                pauseCounter = 0.f;
            }

            pauseCounter += deltaTime;
            // Use the stored current pause duration
            if (pauseCounter >= currentPauseDuration) {
                fadeOut = false; // Begin fade-in
                pauseAtBlack = false;
                pauseCounter = 0.f;
            }
        }
    }
    else {
        // Use the stored current speed
        alpha -= currentFadeInSpeed * deltaTime;
        if (alpha <= 0.f) {
            alpha = 0.f;
            isTransitioning = false;
            onFullBlackCallback = nullptr; // Clear callback after finish
        }
    }

    fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<uint8_t>(alpha)));
}

void Transition::render(sf::RenderWindow& window) {
    if (isTransitioning || static_cast<int>(alpha) > 0) {
        window.draw(fadeRect);
    }
}
