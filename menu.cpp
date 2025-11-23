#include "PCH.h"
#include "Menu.h"
#include "Game.h"

void Menu::initMenu() {
    if (font2.openFromFile("Assets/Fonts/ui.ttf")) {
        std::cout << "UI font loaded!" << std::endl;
    }
    if (font1.openFromFile("Assets/Fonts/Belanosima-Bold.ttf")) {
        std::cout << "UI font loaded!" << std::endl;
    }

    float startY = 350.f;
    float spacing = 120.f;
    text1.setFont(font1);
    text1.setCharacterSize(50);
    text1.setFillColor(sf::Color::White);
    text1.setOutlineColor(sf::Color::Black);
    text1.setOutlineThickness(3.f);

    std::vector<std::string> mainMenuLabels = { "Continue", "New Game", "Controls", "Exit" };

    for (int i = 0; i < 4; i++) {
        text1.setString(mainMenuLabels[i]);
        text1.setOrigin(text1.getGlobalBounds().size / 2.f);
        text1.setPosition({ 960, startY + i * spacing });
        mainMenuText.push_back(text1);
    }

    std::vector<std::string> controlsMenuLabels = { "Move Left : A", "Move Right : D", "Jump : Space", "Sprint : Shift", "Back" };

    for (int i = 0; i < 5; i++) {
        text1.setString(controlsMenuLabels[i]);
        text1.setOrigin(text1.getGlobalBounds().size / 2.f);
        text1.setPosition({ 960, startY - 50 + i * spacing });
        controlsMenuText.push_back(text1);
    }

    std::vector<std::string> confirmationMenuLabels = { "Are you sure?", "No", "Yes" };

    for (int i = 0; i < 3; i++) {
        text1.setString(confirmationMenuLabels[i]);
        text1.setOrigin(text1.getGlobalBounds().size / 2.f);
        if (i == 0) {
            text1.setPosition({ 960, startY + spacing });
        }
        else if (i == 1) {
            text1.setPosition({ 960 - 100, startY + 2 * spacing });
        }
        else {
            text1.setPosition({ 960 + 100, startY + 2 * spacing });
        }
        confirmationMenuText.push_back(text1);
    }

    text2.setOutlineThickness(5.f);

    text2.setCharacterSize(100);
    text2.setString("Room 629");
    text2.setOrigin(text2.getGlobalBounds().size / 2.f);
    text2.setPosition({ 960, 200 });
    titleScreenText.push_back(text2);

    text2.setCharacterSize(50);
    text2.setString("Press Enter to Start");
    text2.setOrigin(text2.getGlobalBounds().size / 2.f);
    text2.setPosition({ 960, 880 });
    titleScreenText.push_back(text2);
}

Menu::Menu(Game* gamePtr) : game(gamePtr), text1(font1, "", 0), text2(font2, "", 0) {
    initMenu();
}

std::vector<sf::Text> Menu::getTitleScreenText() { return titleScreenText; }
std::vector<sf::Text> Menu::getMainMenuText() { return mainMenuText; }
std::vector<sf::Text> Menu::getControlsMenuText() { return controlsMenuText; }
std::vector<sf::Text> Menu::getConfirmationMenuText() { return confirmationMenuText; }
