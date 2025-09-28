#include "PCH.h"
#include "Door.h"
#include "Game.h"

// Default constructor
Door::Door(int _id, const sf::FloatRect& _bounds, int _targetRoomId, const sf::Vector2f& _spawn)
    : id(_id), bounds(_bounds), targetRoomId(_targetRoomId), spawnPos(_spawn)
{
}