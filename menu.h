#pragma once

#include "pch.h"

class Game;

class Menu {
private:
    Game* game; // Pointer to the main game instance

    // Texture containing the buttons
    sf::Texture continueButtonTexture; 
    sf::Texture newGameButtonTexture;
    sf::Texture controlsButtonTexture;
    sf::Texture exitButtonTexture;

    int buttonSize = 120;
    int continueX = 1, continueY = 0;
    int newGameX = 0, newGameY = 0;
    int controlsX = 1, controlsY = 2;
    int exitX = 2, exitY = 1;

    void initMenu(); // Load texture and set initial values

public:
    // Sprite representing the buttons
    sf::Sprite continueButton;
    sf::Sprite newGameButton;
    sf::Sprite controlsButton;
    sf::Sprite exitButton;

    Menu(Game* gamePtr);

    // Return the player sprite for Game class
    sf::Sprite& getContinueButton();
    sf::Sprite& getNewGameButton();
    sf::Sprite& getControlsButton();
    sf::Sprite& getExitButton();
};