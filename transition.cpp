#include "pch.h"
#include "transition.h"
#include <iostream>

transition::transition(float pauseTime)
    : alpha(0.f)
    , isTransitioning(false)
    , fadeOut(true)
    , pauseAtBlack(false)
    , pauseCounter(0.f)
    , pauseDuration(pauseTime)
    , onFullBlackCallback(nullptr)
{
    fadeRect.setSize({ 1920.f, 1080.f });
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));
}

void transition::start(std::function<void()> onFullBlack) {
    isTransitioning = true;
    fadeOut = true;
    alpha = 0.f;
    pauseAtBlack = false;
    pauseCounter = 0.f;
    onFullBlackCallback = onFullBlack;
}

void transition::reset() {
    isTransitioning = false;
    fadeOut = true;
    alpha = 0.f;
    pauseAtBlack = false;
    pauseCounter = 0.f;
    onFullBlackCallback = nullptr;
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));
}

void transition::update(float deltaTime) {
    if (!isTransitioning) return;

    if (fadeOut) {
        alpha += 400.f * deltaTime;
        if (alpha >= 255.f) {
            alpha = 255.f;

            if (!pauseAtBlack) {
                // call stored callback once when fully black
                if (onFullBlackCallback) {
                    onFullBlackCallback();
                }
                pauseAtBlack = true;
                pauseCounter = 0.f;
            }

            pauseCounter += deltaTime;
            if (pauseCounter >= pauseDuration) {
                fadeOut = false; // begin fade-in
                pauseAtBlack = false;
                pauseCounter = 0.f;
            }
        }
    }
    else {
        alpha -= 500.f * deltaTime;
        if (alpha <= 0.f) {
            alpha = 0.f;
            isTransitioning = false;
            onFullBlackCallback = nullptr; // clear callback after finish
        }
    }

    fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<uint8_t>(alpha)));
}

void transition::render(sf::RenderWindow& window) {
    if (isTransitioning || static_cast<int>(alpha) > 0) {
        window.draw(fadeRect);
    }
}