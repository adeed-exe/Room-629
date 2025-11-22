#include "PCH.h"
#include "Item.h"
#include "Game.h"
#include "HUD.h"

// Default constructor

Item::Item(int _roomId, int _itemId, const sf::FloatRect& _bounds, const sf::Vector2f _drawPos)
	: roomId(_roomId), itemId(_itemId), bounds(_bounds), drawPos(_drawPos)
{
}