#pragma once

#include "PCH.h"

class Game;

struct GameState {
    sf::Vector2f playerPos = { 1253.f, 180.f };
    float curStamina = 100.f;
    float curFatigue = 0.f;

    std::multiset<int> items;

    int currentRoomId = 0;
    int progress = 0; // Incrementing depicts progress

    std::vector<int> roomInfo = std::vector<int>(7); // Whether items at each room are picked or not
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

