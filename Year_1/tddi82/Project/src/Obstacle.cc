#include "Obstacle.h"

Obstacle::Obstacle(std::pair<int, int> const& pos, Hitbox const& hb,
                   ENTITY_TYPE obstacleType)
    : Entity{pos, hb} {
    /* Static sprites */
    if (obstacleType == ISLAND) {
        texture.loadFromFile("resources/island.png");
        sprite.setRotation(rand() % 360); // Random rotation
    }

    if (obstacleType == SHIP_WRECK) {
        texture.loadFromFile("resources/wreck.png");
        sprite.setRotation(rand() % 360); // Random rotation
    }

    sprite.setTexture(texture);

    /* Set sprite origin to center of sprite texture */
    sprite.setOrigin(sprite.getLocalBounds().width / 2,
                     sprite.getLocalBounds().height / 2);
}