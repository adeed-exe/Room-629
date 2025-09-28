#pragma once
#include "PCH.h"

struct Door {
    int id = 0;
    sf::FloatRect bounds{};
    int targetRoomId = -1; // ID of room to change to, -1 = none
    sf::Vector2f spawnPos; // Player spawn position when entering target room

    Door(int _id, const sf::FloatRect& _bounds, int _targetRoomId, const sf::Vector2f& _spawn);
};