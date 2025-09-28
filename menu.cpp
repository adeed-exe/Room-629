#include "PCH.h"
#include "Menu.h"
#include "Game.h"

void Menu::initMenu() {
    if (font.openFromFile("Assets/Fonts/ui.ttf")) {
        std::cout << "UI font loaded!" << std::endl;
    }

    float startY = 350.f;
    float spacing = 120.f;
    std::vector<std::string> mainMenuLabels = { "Continue", "New Game", "Controls", "Exit" };

    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(3.f);

    for (int i = 0; i < 4; i++) {
        text.setString(mainMenuLabels[i]);
        text.setOrigin(text.getGlobalBounds().size / 2.f);
        text.setPosition({ 960, startY + i * spacing });
        mainMenuText.push_back(text);
    }

    float startY2 = 350.f;
    std::vector<std::string> controlsMenuLabels = { "Move Left : A", "Move Right : D", "Jump : Space", "Sprint : Hold Shift", "Back" };

    for (int i = 0; i < 5; i++) {
        text.setString(controlsMenuLabels[i]);
        text.setOrigin(text.getGlobalBounds().size / 2.f);
        text.setPosition({ 960, startY - 50 + i * spacing });
        controlsMenuText.push_back(text);
    }

    text.setOutlineThickness(5.f);

    text.setCharacterSize(100);
    text.setString("Room 629");
    text.setOrigin(text.getGlobalBounds().size / 2.f);
    text.setPosition({ 960, 200 });
    titleScreenText.push_back(text);

    text.setCharacterSize(50);
    text.setString("Press Enter to Start");
    text.setOrigin(text.getGlobalBounds().size / 2.f);
    text.setPosition({ 960, 880 });
    titleScreenText.push_back(text);
}

Menu::Menu(Game* gamePtr) : game(gamePtr), text(font, "", 0) {
    initMenu();
}

std::vector<sf::Text> Menu::getTitleScreenText() { return titleScreenText; }
std::vector<sf::Text> Menu::getMainMenuText() { return mainMenuText; }
std::vector<sf::Text> Menu::getControlsMenuText() { return controlsMenuText; }