#include "PCH.h"
#include "ViewSystem.h"
#include "Game.h"

ViewSystem::ViewSystem(Game* gamePtr) : game(gamePtr)
{
    sf::Vector2f bounds = game->background.getLocalBounds().size;
    float aspectRatio = 16.f / 9.f;

    // Sets the viewer to the screen aspect ratio
    view.setSize({ bounds.y * aspectRatio, bounds.y });
    view.setCenter({ bounds.x / 2.f , bounds.y / 2.f });
}

void ViewSystem::update(const sf::Vector2f& targetPos) {
    sf::Vector2f center = targetPos;
    sf::Vector2f bounds = game->background.getLocalBounds().size;
    float aspectRatio = 16.f / 9.f;

    // Clamp so the view doesn't go past the level edges
    float viewWidth = bounds.y * aspectRatio;
    float viewHeight = bounds.y;
    float halfWidth = viewWidth / 2.f;
    float halfHeight = viewHeight / 2.f;

    if (center.x < halfWidth) center.x = halfWidth;
    if (center.y < halfHeight) center.y = halfHeight;
    if (center.x > bounds.x - halfWidth) center.x = bounds.x - halfWidth;
    if (center.y > bounds.y - halfHeight) center.y = bounds.y - halfHeight;

    view.setCenter(sf::Vector2f({ center.x, center.y }));
}

const sf::View& ViewSystem::getView() const {
    return view;
}