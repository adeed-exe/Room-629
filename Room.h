#pragma once
#include "PCH.h"
#include "Door.h"
#include "Item.h"

class Room {
private:
    int id = -1;
    std::string texturePath;
    sf::Texture texture;
    sf::Sprite background;
    std::vector<Door> doors;
    sf::Vector2f spawn{ 80.f, 180.f };

    //std::vector<Item> items;

public:
    // Default constructor
    Room();

    // Parameterized constructor
    Room(int id, const std::string& texturePath, const sf::Vector2f& spawn);

    bool loadTexture(); // Loads texture if needed
    void applyToSprite(sf::Sprite& target); // Apply texture to external sprite

    int getId() const { return id; }
    const std::vector<Door>& getDoors() const { return doors; }
    void addDoor(const Door& d) { doors.push_back(d); }
    const sf::Vector2f& getSpawn() const { return spawn; }
    const std::string& getTexturePath() const { return texturePath; }

    //void addItem(const Item& i) { items.push_back(i); }
};