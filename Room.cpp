#include "PCH.h"
#include "Room.h"
#include "Game.h"

// Default constructor
Room::Room()
    : id(-1), texturePath(""), spawn({ 80.f, 180.f }), background(texture)
{
}

// Parameterized constructor
Room::Room(int id_, const std::string& texturePath_, const sf::Vector2f& spawnPos)
    : id(id_), texturePath(texturePath_), spawn(spawnPos), background(texture)
{
}

// Load texture if not already loaded
bool Room::loadTexture() {
    if (texture.getSize().x > 0) return true;
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Room::loadTexture() failed for: " << texturePath << std::endl;
        return false;
    }
    background.setTexture(texture, true);
    background.setOrigin({ background.getLocalBounds().size.x / 2.f, background.getLocalBounds().size.y / 2.f });
    return true;
}

// Apply room texture to external sprite
void Room::applyToSprite(sf::Sprite& target) {
    if (!loadTexture()) return;
    target.setTexture(texture, true);
    target.setOrigin(background.getOrigin());
}
