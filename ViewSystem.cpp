#include "pch.h"
#include "ViewSystem.h"

ViewSystem::ViewSystem(float screenWidth, float screenHeight, float levelWidth, float levelHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
    levelWidth(levelWidth), levelHeight(levelHeight)
{

    float aspectRatio = 1920.f / 1080.f;
    
    //sets the viewer to the screen aspect ratio
    
    view.setSize(sf::Vector2f({screenHeight * aspectRatio, screenHeight })); 
    
    view.setCenter(sf::Vector2f({ screenWidth/2.f , screenHeight/2.f }));
}

void ViewSystem::update(const sf::Vector2f& targetPos) {
    sf::Vector2f center = targetPos;
    float aspectRatio = 1920.f / 1080.f;


    // Clamp so the view doesn't go past the level edges
    float viewWidth = screenHeight * aspectRatio;
    float viewHeight = screenHeight;
    float halfWidth = viewWidth / 2.f;
    float halfHeight = viewHeight / 2.f;

    if (center.x < halfWidth) center.x = halfWidth;
    if (center.y < halfHeight) center.y = halfHeight;
    if (center.x > levelWidth - halfWidth) center.x = levelWidth - halfWidth;
    if (center.y > levelHeight - halfHeight) center.y = levelHeight - halfHeight;

    view.setCenter(sf::Vector2f({ center.x - 10, center.y }));
}

const sf::View& ViewSystem::getView() const {
    return view;
}
