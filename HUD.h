#pragma once

#include "PCH.h"

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
    sf::Text itemText;
    sf::Texture coffeeTexture;
    sf::Texture markerTexture;
    sf::Texture chocolateTexture;
    sf::Texture paperTexture;

    float itemOffset = 43.f;

    void initHUD();

public:
    sf::Text subtitleText;
    sf::Sprite coffee;
    sf::Sprite marker;
    sf::Sprite chocolate;
    sf::Sprite paper;

	std::vector<sf::Sprite> itemSprites;

    // Values
    float stamina;
    float maxStamina;
    float fatigue;
    float maxFatigue;

    HUD(Game* gamePtr);

    void update(float deltaTime, bool isRunning);
    void render(sf::RenderWindow& window);

    void setSubtitle(const std::string& text);

    sf::RectangleShape& getHud();
};