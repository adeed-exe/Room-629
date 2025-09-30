#pragma once

#include "PCH.h"

class Game;

struct GameState {
    sf::Vector2f playerPos = { 1253.f, 180.f };
    float curStamina = 100.f;
    float curFatigue = 0.f;

    // Inventory slots, 0 means empty, else contains item IDs
    std::vector<int> inventorySlots = std::vector<int>(10, 0);

    int currentRoomId = 0;
    int progress = 0; // Incrementing depicts progress
};

class SaveSystem {
private:
    Game* game;

public:
	SaveSystem(Game* gamePtr);

    bool fileExists(const std::string& filePath);
	bool save(const std::string& filePath, const GameState& state);
	bool load(const std::string& filePath, GameState& state);
	bool reset(const std::string& filePath, const GameState& state);
};

