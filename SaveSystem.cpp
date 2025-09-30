#include "PCH.h"
#include "SaveSystem.h"
#include "Game.h"

SaveSystem::SaveSystem(Game* gamePtr) : game(gamePtr) {

}

bool SaveSystem::fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.is_open();
}

bool SaveSystem::save(const std::string& filePath, const GameState& state) {
    std::ofstream out(filePath, std::ios::out);

    if (!out.is_open()) {
        std::cerr << "Failed to open file for saving: " << filePath << "\n";
        return false;
    }
    
    // Write player position
    out << state.playerPos.x << " " << state.playerPos.y << "\n";

    // Write stamina + fatigue
    out << state.curStamina << " " << state.curFatigue << "\n";

    // Write inventory
    for (int i = 0; i < state.inventorySlots.size(); i++) {
        out << state.inventorySlots[i];
        if (i < state.inventorySlots.size() - 1) {
            out << " ";
        }
    }
    out << "\n";

    // Write room + progress
    out << state.currentRoomId << " " << state.progress << "\n";

    return true;
}

bool SaveSystem::load(const std::string& filePath, GameState& state) {
    std::ifstream in(filePath, std::ios::in);

    if (!in.is_open()) {
        std::cerr << "Failed to open file for loading: " << filePath << "\n";
        return false;
    }

    // Write player position
    in >> state.playerPos.x >> state.playerPos.y;

    // Read stamina + fatigue
    in >> state.curStamina >> state.curFatigue;

    // Read inventory
    for (int i = 0; i < state.inventorySlots.size(); i++) {
        in >> state.inventorySlots[i];
    }

    // Read room + progress
    in >> state.currentRoomId >> state.progress;

    return true;
}

bool SaveSystem::reset(const std::string& filePath, const GameState& state) {
    std::ofstream out(filePath, std::ios::out);

    if (!out.is_open()) {
        std::cerr << "Failed to open file for saving: " << filePath << "\n";
        return false;
    }

    // Write player position
    out << 1253 << " " << 180 << "\n";

    // Write stamina + fatigue
    out << 100 << " " << 0 << "\n";

    // Write inventory
    for (int i = 0; i < state.inventorySlots.size(); i++) {
        out << 0;
        if (i < state.inventorySlots.size() - 1) {
            out << " ";
        }
    }
    out << "\n";

    // Write room + progress
    out << 0 << " " << 0 << "\n";

    return true;
}