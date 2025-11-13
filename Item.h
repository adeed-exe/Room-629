#pragma once
#include "PCH.h"

struct Item {
    int id = 0;
    sf::FloatRect bounds{};
    int targetRoomId = -1; // ID of room to change to, -1 = none
    sf::Vector2f spawnPos; // Player spawn position when entering target room
    std::string texturePath;
    bool picked;

    Item(int _id, const sf::FloatRect& _bounds, int _targetRoomId, const sf::Vector2f& _spawn, std::string _texturePath, bool _picked = false);
};