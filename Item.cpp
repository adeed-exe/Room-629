#include "PCH.h"
#include "Item.h"
#include "Game.h"

// Default constructor
Item::Item(int _id, const sf::FloatRect& _bounds, std::string _texturePath)
    : id(_id), bounds(_bounds), texturePath(_texturePath)
{
}
