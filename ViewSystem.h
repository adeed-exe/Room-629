#pragma once
#include "pch.h"

class ViewSystem {
private:
    float screenWidth;
    float screenHeight;
    float levelWidth;
    float levelHeight;
    sf::View view;

public:
    ViewSystem(float screenWidth, float screenHeight, float levelWidth, float levelHeight);
    void update(const sf::Vector2f& targetPos);
    const sf::View& getView() const;
};
