#include "PCH.h"
#include "Item.h"
#include "Game.h"

// Default constructor
Item::Item(int _id, const sf::FloatRect& _bounds, int _targetRoomId, const sf::Vector2f& _spawn, std::string _texturePath, bool _picked)
    : id(_id), bounds(_bounds), targetRoomId(_targetRoomId), spawnPos(_spawn), texturePath(_texturePath), picked(_picked)
{
}