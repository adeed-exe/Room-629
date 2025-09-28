#pragma once
#include "PCH.h"

class Game;

class ViewSystem {
private:
    Game* game; // Pointer to the main game instance
    sf::View view;

public:
    ViewSystem(Game* gamePtr);
    void update(const sf::Vector2f& targetPos);
    const sf::View& getView() const;
};