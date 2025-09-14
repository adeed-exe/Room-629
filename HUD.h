#pragma once

#include "pch.h"  
#include <string>

class Game;

class HUD {
private:
    Game* game; // Pointer to the main game instance

    // Bars
    sf::RectangleShape staminaBarBack;
    sf::RectangleShape staminaBarFront;

    sf::RectangleShape fatigueBarBack;
    sf::RectangleShape fatigueBarFront;

    // Subtitle
   
    sf::Font font;

    // Values
    float stamina;
    float maxStamina;
    float fatigue;
    float maxFatigue;

    void initHUD();

public:
    sf::Text subtitleText;

    HUD(Game* gamePtr);

    void update(float deltaTime, bool isRunning, bool isCrouching);
    void render(sf::RenderWindow& window);

    void setSubtitle(const std::string& text);
};
