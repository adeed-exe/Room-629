#include "pch.h"
#include "Transition.h"


transition::transition(float pauseTime) {
    //initialize transition fade
    fadeRect.setSize({ 1920.f, 1080.f });
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));

    alpha = 0.f;
    isTransitioning = false;
    fadeOut = true;
    pauseAtBlack = false;
    pauseCounter = 0.f;
    pauseDuration = pauseTime;
}

void transition::start() {
    //sets the transition to begin
    isTransitioning = true;
    fadeOut = true;
    alpha = 0.f;
    pauseAtBlack = false;
    pauseCounter = 0.f;
}

void transition::update(float deltaTime, std::function<void()> onBlack) {
    //                                     ^ this calls the function which it was called from directly
    if (!isTransitioning) return;

    //darkens the screen
    if (fadeOut) {
        alpha += 400.f * deltaTime;
        if (alpha >= 255.f) {
            alpha = 255.f;

            // trigger background swap when fully black
            if (!pauseAtBlack && onBlack) {
                onBlack(); 
                pauseAtBlack = true;
                pauseCounter = 0.f;
            }

            pauseCounter += deltaTime;

            if (pauseCounter >= pauseDuration) {
                fadeOut = false;   // start to fade-in
                pauseAtBlack = false;
            }
        }
    }

    //lightens the screen
    else {
        alpha -= 500.f * deltaTime;
        if (alpha <= 0.f) {
            alpha = 0.f;
            isTransitioning = false;
        }
    }

    std :: cout << "Alpha : " << alpha << " // deltaTime :  " << deltaTime << "\n";
    //sets the screen alpha
    fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<uint8_t>(alpha)));
}

void transition::render(sf::RenderWindow& window) {
    if (isTransitioning) {
        window.draw(fadeRect);
    }
}