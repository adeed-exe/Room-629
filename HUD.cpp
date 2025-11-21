#include "PCH.h"
#include "HUD.h"
#include "Game.h"

void HUD::initHUD() {
    if (!font.openFromFile("Assets/Fonts/ui.ttf")) {
        std::cout << "Failed to load HUD font!" << std::endl;
    }

    if (coffeeTexture.loadFromFile("Assets/Sprites/item_coffee.png")) {
        std::cout << "Coffee texture loaded!" << std::endl;
    }
    if (markerTexture.loadFromFile("Assets/Sprites/item_marker.png")) {
        std::cout << "Marker texture loaded!" << std::endl;
    }
    if (chocolateTexture.loadFromFile("Assets/Sprites/item_chocolate.png")) {
        std::cout << "Chocolate texture loaded!" << std::endl;
    }
    if (paperTexture.loadFromFile("Assets/Sprites/item_paper.png")) {
        std::cout << "Paper texture loaded!" << std::endl;
    }

    coffee.setTexture(coffeeTexture, true);
	coffee.setScale({ 0.5f, 0.5f });
	coffee.setOrigin(coffee.getLocalBounds().size / 2.f);
    marker.setTexture(markerTexture, true);
	marker.setScale({ 0.5f, 0.5f });
	marker.setOrigin(marker.getLocalBounds().size / 2.f);
    chocolate.setTexture(chocolateTexture, true);
    chocolate.setScale({ 0.5f, 0.5f });
    chocolate.setOrigin(chocolate.getLocalBounds().size / 2.f);
    paper.setTexture(paperTexture, true);
    paper.setScale({ 0.5f, 0.5f });
    paper.setOrigin(paper.getLocalBounds().size / 2.f);

    itemSprites.push_back(coffee);
    itemSprites.push_back(chocolate);
    itemSprites.push_back(marker);
    itemSprites.push_back(paper);

    // Bar sizes
    maxStamina = 100.f;
    stamina = game->gameState.curStamina;
    maxFatigue = 100.f;
    fatigue = game->gameState.curFatigue;

    // Stamina bar
    staminaBarBack.setSize({ 130.f, 10.f });
    staminaBarBack.setOrigin(staminaBarBack.getLocalBounds().size / 2.f);
    staminaBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    
    staminaBarFront.setSize({ 130.f, 10.f });
    staminaBarFront.setOrigin(staminaBarBack.getLocalBounds().size / 2.f);
    staminaBarFront.setFillColor(sf::Color::Green);
    
    // Fatigue bar
    fatigueBarBack.setSize({ 130.f, 10.f });
    fatigueBarBack.setOrigin(staminaBarBack.getLocalBounds().size / 2.f);
    fatigueBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    
    fatigueBarFront.setSize({ 130.f, 10.f });
    fatigueBarFront.setOrigin(staminaBarBack.getLocalBounds().size / 2.f);
    fatigueBarFront.setFillColor(sf::Color::Red);
    
    // Subtitle
    subtitleText.setFont(font);
    subtitleText.setCharacterSize(28);
    subtitleText.setFillColor(sf::Color::White);
    subtitleText.setOutlineColor(sf::Color::Black);
    subtitleText.setOutlineThickness(2.f);
    subtitleText.setPosition(sf::Vector2f(1920.f / 2.f - 300.f, 900.f)); // Bottom center-ish 

    // Item text
    itemText.setFont(font);
    itemText.setString("Items :");
    itemText.setCharacterSize(10);
    itemText.setFillColor(sf::Color::White);
    itemText.setOutlineColor(sf::Color::Black);
    itemText.setOutlineThickness(2.f);
	itemText.setOrigin(itemText.getLocalBounds().size / 2.f);
    itemText.setPosition(sf::Vector2f(17.5f + itemText.getLocalBounds().size.x / 2.f, 282.5f));
}

HUD::HUD(Game* gamePtr) : game(gamePtr), subtitleText(font, "", 0), itemText(font,"",0),
    coffee(coffeeTexture), marker(markerTexture), chocolate(chocolateTexture), paper(paperTexture) {
    initHUD();
}

void HUD::update(float deltaTime, bool isRunning) {
    // Handle stamina logic
    if (isRunning && stamina > 0.f) {
        stamina -= 10.f * deltaTime; // Drain faster while running
        if (stamina < 0.f) stamina = 0.f;
    }
    else {
        stamina += 20.f * deltaTime; // Regenerate stamina
        if (stamina > maxStamina) stamina = maxStamina;
    }

    // Handle fatigue logic
    if (isRunning) {
        fatigue += 15.f * deltaTime; // Accumulate fatigue
        if (fatigue > maxFatigue) fatigue = maxFatigue;
    }
    else {
        fatigue -= 10.f * deltaTime; // Reduce fatigue
        if (fatigue < 0.f) fatigue = 0.f;
    }

    // Update bar sizes
    staminaBarFront.setSize({ (stamina / maxStamina) * 130.f, 10.f });
    fatigueBarFront.setSize({ (fatigue / maxFatigue) * 130.f, 10.f });
    float screenWidth = game->background.getLocalBounds().size.x;
    float staminaOffsetLeft = 76.8f;
    float staminaOffsetRight = screenWidth - 456.8f;
    float fatigueOffsetLeft = 456.8f;
    float fatigueOffsetRight = screenWidth - 76.8f;
    float itemOffsetLeft = 8.5f + itemText.getLocalBounds().size.x / 2.f;
    float itemOffsetRight = screenWidth - 493;

    staminaBarBack.setPosition({ std::max(staminaOffsetLeft, std::min(staminaOffsetRight, game->player->getPlayer().getPosition().x - 190)), 15});
    staminaBarFront.setPosition({ std::max(staminaOffsetLeft, std::min(staminaOffsetRight, game->player->getPlayer().getPosition().x - 190)), 15 });
    fatigueBarBack.setPosition({ std::max(fatigueOffsetLeft, std::min(fatigueOffsetRight, game->player->getPlayer().getPosition().x + 190)), 15 });
    fatigueBarFront.setPosition({ std::max(fatigueOffsetLeft, std::min(fatigueOffsetRight, game->player->getPlayer().getPosition().x + 190)), 15 });
    itemText.setPosition({ std::max(itemOffsetLeft, std::min(itemOffsetRight, game->player->getPlayer().getPosition().x - 226.7f)), 282.5f });
}

void HUD::render(sf::RenderWindow& window) {

    window.draw(itemText);

    window.draw(staminaBarBack);
    window.draw(staminaBarFront);

    window.draw(fatigueBarBack);
    window.draw(fatigueBarFront);

    window.draw(subtitleText);
	
    int index = 0;
    for (auto i : game->gameState.items) {
        itemSprites[i].setPosition({itemOffset + itemText.getPosition().x + index * 30.f, itemText.getPosition().y});
        window.draw(itemSprites[i]);
        index++;
	}
}

void HUD::setSubtitle(const std::string& text) {
    subtitleText.setString(text);

    // Center subtitle
    sf::FloatRect bounds = subtitleText.getLocalBounds();
    subtitleText.setOrigin({ bounds.size.x / 2.f, 0.f });
    subtitleText.setPosition(sf::Vector2f(1920.f/2.f ,900.f) );
}

sf::RectangleShape& HUD::getHud() { return staminaBarBack; }
