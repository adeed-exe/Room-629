#include "pch.h"
#include "hud.h"
#include "game.h"

void HUD::initHUD() {
    if (!font.openFromFile("Assets/Fonts/ui.ttf")) {
        std::cout << "Failed to load HUD font!" << std::endl;
    }

    // Bars sizes
    maxStamina = 100.f;
    stamina = maxStamina;
    maxFatigue = 100.f;
    fatigue = 0.f;

    // Stamina bar
    staminaBarBack.setSize({ 300.f, 20.f });
    staminaBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    staminaBarBack.setPosition(sf::Vector2f(50.f, 50.f));

    staminaBarFront.setSize({ 300.f, 20.f });
    staminaBarFront.setFillColor(sf::Color::Green);
    staminaBarFront.setPosition(sf::Vector2f(50.f, 50.f));

    // Fatigue bar
    fatigueBarBack.setSize({ 300.f, 20.f });
    fatigueBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    fatigueBarBack.setPosition(sf::Vector2f(50.f, 80.f));

    fatigueBarFront.setSize({ 300.f, 20.f });
    fatigueBarFront.setFillColor(sf::Color::Red);
    fatigueBarFront.setPosition(sf::Vector2f(50.f, 50.f));

    // Subtitle
    subtitleText.setFont(font);
    subtitleText.setCharacterSize(28);
    subtitleText.setFillColor(sf::Color::White);
    subtitleText.setOutlineColor(sf::Color::Black);
    subtitleText.setOutlineThickness(2.f);
    subtitleText.setPosition(sf::Vector2f(1920.f / 2.f - 300.f, 900.f)); // bottom center-ish
}

HUD::HUD(Game* gamePtr) : game(gamePtr), subtitleText(font, "", 0) {
    initHUD();
}

void HUD::update(float deltaTime, bool isRunning, bool isCrouching) {
    // Handle stamina logic
    if (isRunning && stamina > 0.f) {
        stamina -= 30.f * deltaTime; // drain faster while running
        if (stamina < 0.f) stamina = 0.f;
    }
    else {
        stamina += 20.f * deltaTime; // regenerate stamina
        if (stamina > maxStamina) stamina = maxStamina;
    }

    // Handle fatigue logic
    if (isRunning) {
        fatigue += 15.f * deltaTime; // accumulate fatigue
        if (fatigue > maxFatigue) fatigue = maxFatigue;
    }
    else {
        fatigue -= 10.f * deltaTime; // reduce fatigue
        if (fatigue < 0.f) fatigue = 0.f;
    }

    // Update bar sizes
    staminaBarFront.setSize({ (stamina / maxStamina) * 300.f, 20.f });
    fatigueBarFront.setSize({ (fatigue / maxFatigue) * 300.f, 20.f });
}

void HUD::render(sf::RenderWindow& window) {
    window.draw(staminaBarBack);
    window.draw(staminaBarFront);

    window.draw(fatigueBarBack);
    window.draw(fatigueBarFront);

    window.draw(subtitleText);
}

void HUD::setSubtitle(const std::string& text) {
    subtitleText.setString(text);

    // Center subtitle
    sf::FloatRect bounds = subtitleText.getLocalBounds();
    subtitleText.setOrigin({ bounds.size.x / 2.f, 0.f });
    subtitleText.setPosition(sf::Vector2f(1920.f/2.f ,900.f) );
}
