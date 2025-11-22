#pragma once
#include "PCH.h"
#include "HUD.h"

struct Item {
    int roomId = 0;
    int itemId = 0;
    sf::FloatRect bounds{};
    sf::Vector2f drawPos;

    Item(int _roomId, int _itemId, const sf::FloatRect& _bounds, const sf::Vector2f _drawPos);
};