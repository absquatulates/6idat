#include "Canonball.h"

#include <cmath>

Cannonball::Cannonball(std::pair<int, int> const& pos, double const dir,
                       double const speed, int const dmg)
    : DynamicEntity{pos,
                    Hitbox{15, 15, 15, 15},
                    dir,
                    speed,
                    {std::cos(dir) * speed, std::sin(dir) * speed}},
      damage{dmg} {
    type = CANNONBALL;
    texture.loadFromFile("resources/cannonball.png");
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2,
                     sprite.getLocalBounds().height / 2);
    sprite.setScale(0.3, 0.3);
}

void Cannonball::handleCollide(Entity* other) {
    if (dynamic_cast<Ship*>(other) != nullptr) {
        dynamic_cast<Ship*>(other)->hit(damage);
    }

    didHit = true;
}

bool Cannonball::isAlive() {
    auto velocityX = velocity.first;
    auto velocityY = velocity.second;
    bool velocityTooLow = std::sqrt(velocityX * velocityX + velocityY * velocityY) < speed / 2;
    return !didHit && out_of_bounds() && !velocityTooLow;
}

void Cannonball::update() {
    // Update position based on velocity
    pos.first += velocity.first;
    pos.second += velocity.second;
    // Slow down over time
    velocity.first *= 0.99;
    velocity.second *= 0.99;
    // Update sprite position and rotation
    sprite.setPosition(pos.first, pos.second);
}