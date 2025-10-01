#pragma once

#include "PCH.h"

class Game;

class SoundSystem {
private:
    Game* game;

    sf::SoundBuffer backgroundBuffer;
    sf::SoundBuffer footstepBuffer;
    sf::SoundBuffer buttonBuffer;
    sf::SoundBuffer startBuffer;
    sf::SoundBuffer doorBuffer;

    sf::Sound backgroundMusic;
    sf::Sound footstepSound;
    sf::Sound buttonSound;
    sf::Sound startSound;
    sf::Sound doorSound;

public:
    SoundSystem(Game* gamePtr);

    void initSounds();

    void playBackgroundMusic();
    void playFootstepSound(float volumeMultiplier);
    void playButtonSound();
    void playStartSound();
    void playDoorSound();
};