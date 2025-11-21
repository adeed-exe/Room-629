#pragma once
#include "PCH.h"

struct Item {
    int id = 0;
    sf::FloatRect bounds{};
    std::string texturePath;

    Item(int _id, const sf::FloatRect& _bounds, std::string _texturePath);
};