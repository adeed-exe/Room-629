#pragma once

#include "PCH.h"

class Game;

class Menu {
private:
    Game* game; // Pointer to the main game instance

    sf::Font font; // Font for the UI text

    void initMenu(); // Load texture and set initial values

public:
    // UI buttons
    sf::Text text;
    std::vector<sf::Text> titleScreenText;
    std::vector<sf::Text> mainMenuText;
    std::vector<sf::Text> controlsMenuText;
    std::vector<sf::Text> confirmationMenuText;

    Menu(Game* gamePtr);

    // Return the player sprite for Game class
    std::vector<sf::Text> getTitleScreenText();
    std::vector<sf::Text> getMainMenuText();
    std::vector<sf::Text> getControlsMenuText();
    std::vector<sf::Text> getConfirmationMenuText();
};