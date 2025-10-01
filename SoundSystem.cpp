#include "PCH.h"
#include "SoundSystem.h"
#include "Game.h"

SoundSystem::SoundSystem(Game* gamePtr)
	: game(gamePtr), backgroundMusic(backgroundBuffer), footstepSound(footstepBuffer),
	buttonSound(buttonBuffer), startSound(startBuffer), doorSound(doorBuffer)
{
	initSounds();
}

void SoundSystem::initSounds() {
	if (backgroundBuffer.loadFromFile("Assets/Sounds/backgroundMusic.wav")) {
		std::cout << "Background music loaded!" << std::endl;
	}
	backgroundMusic.setBuffer(backgroundBuffer);
	backgroundMusic.setLooping(true);

	if (footstepBuffer.loadFromFile("Assets/Sounds/footstep.wav")) {
		std::cout << "Background music loaded!" << std::endl;
	}
	footstepSound.setBuffer(footstepBuffer);

	if (buttonBuffer.loadFromFile("Assets/Sounds/button.wav")) {
		std::cout << "Background music loaded!" << std::endl;
	}
	buttonSound.setBuffer(buttonBuffer);

	if (startBuffer.loadFromFile("Assets/Sounds/start.wav")) {
		std::cout << "Background music loaded!" << std::endl;
	}
	startSound.setBuffer(startBuffer);

	if (doorBuffer.loadFromFile("Assets/Sounds/door.wav")) {
		std::cout << "Background music loaded!" << std::endl;
	}
	doorSound.setBuffer(doorBuffer);
}

void SoundSystem::playBackgroundMusic() {
	if (backgroundMusic.getStatus() != sf::Music::Status::Playing) {
		backgroundMusic.play();
	}
}

void SoundSystem::playFootstepSound(float volumeMultiplier) {
	footstepSound.setVolume(100 * volumeMultiplier);
	footstepSound.play();
}

void SoundSystem::playButtonSound() {
	buttonSound.play();
}

void SoundSystem::playStartSound() {
	startSound.play();
}

void SoundSystem::playDoorSound() {
	doorSound.play();
}