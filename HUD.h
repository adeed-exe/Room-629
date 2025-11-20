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

    float itemOffset = 40.f;

    void initHUD();

public:
    sf::Text subtitleText;
    sf::Sprite coffee;
    sf::Sprite marker;

	std::vector<sf::Sprite> itemSprites;
    std::set<int> items;

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