#include "pch.h"
#include "menu.h"
#include "game.h"

void Menu::initMenu() {
    if (continueButtonTexture.loadFromFile("Assets/Sprites/buttons.jpg")) {
        std::cout << "Background texture 1 loaded!" << std::endl;
    }
    continueButton.setTexture(continueButtonTexture, true);
    continueButton.setTextureRect(sf::IntRect({ continueX * buttonSize, continueY * buttonSize }, { buttonSize, buttonSize }));
    continueButton.setPosition({ (1920 - buttonSize) / 2.f, (1080 - buttonSize) / 2.f - 1.5f * buttonSize});

    if (newGameButtonTexture.loadFromFile("Assets/Sprites/buttons.jpg")) {
        std::cout << "Background texture 1 loaded!" << std::endl;
    }
    newGameButton.setTexture(newGameButtonTexture, true);
    newGameButton.setTextureRect(sf::IntRect({ newGameX * buttonSize, newGameY * buttonSize }, { buttonSize, buttonSize }));
    newGameButton.setPosition({ (1920 - buttonSize) / 2.f, (1080 - buttonSize) / 2.f - 0.5f * buttonSize });

    if (controlsButtonTexture.loadFromFile("Assets/Sprites/buttons.jpg")) {
        std::cout << "Background texture 1 loaded!" << std::endl;
    }
    controlsButton.setTexture(controlsButtonTexture, true);
    controlsButton.setTextureRect(sf::IntRect({ controlsX * buttonSize, controlsY * buttonSize }, { buttonSize, buttonSize }));
    controlsButton.setPosition({ (1920 - buttonSize) / 2.f, (1080 - buttonSize) / 2.f + 0.5f * buttonSize });

    if (exitButtonTexture.loadFromFile("Assets/Sprites/buttons.jpg")) {
        std::cout << "Background texture 1 loaded!" << std::endl;
    }
    exitButton.setTexture(exitButtonTexture, true);
    exitButton.setTextureRect(sf::IntRect({ exitX * buttonSize, exitY * buttonSize }, { buttonSize, buttonSize }));
    exitButton.setPosition({ (1920 - buttonSize) / 2.f, (1080 - buttonSize) / 2.f + 1.5f * buttonSize});
}

Menu::Menu(Game* gamePtr) : game(gamePtr),
continueButton(continueButtonTexture), newGameButton(newGameButtonTexture),
controlsButton(continueButtonTexture), exitButton(exitButtonTexture) {
    initMenu();
}

sf::Sprite& Menu::getContinueButton() { return continueButton; }
sf::Sprite& Menu::getNewGameButton() { return newGameButton; }
sf::Sprite& Menu::getControlsButton() { return controlsButton; }
sf::Sprite& Menu::getExitButton() { return exitButton; }
