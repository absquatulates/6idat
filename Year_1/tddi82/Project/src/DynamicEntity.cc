#include "DynamicEntity.h"

#include <cmath>
#include <math.h>

DynamicEntity::DynamicEntity(std::pair<int, int> const &pos, Hitbox const &hb)
    : Entity{pos, hb}, direction{}, speed{}, velocity{} {}

DynamicEntity::DynamicEntity(std::pair<int, int> const &pos, Hitbox const &hb,
                             double const dir, double const speed,
                             std::pair<float, float> velocity)
    : Entity{pos, hb}, direction{dir}, speed{speed}, velocity{velocity} {}

void DynamicEntity::move(movdir const &movement) {
    if (movement == forward) {
        velocity.first += std::cos(direction) * speed/10;
        velocity.second += std::sin(direction) * speed/10;
    } else if (movement == back) {
        velocity.first -= std::cos(direction) * 0.05;
        velocity.second -= std::sin(direction) * 0.05;
    } else if (movement == left) {
        direction -= 0.1;
    } else if (movement == right) {
        direction += 0.1;
    }
}

void DynamicEntity::update() {
    // Update position based on velocity vector
    pos.first += velocity.first;
    pos.second += velocity.second;

    // Slow down over time
    velocity.first *= 0.99;
    velocity.second *= 0.99;

    sprite.setPosition(pos.first, pos.second);
    // To degrees, and -90 to match intial sprite rotation
    sprite.setRotation((direction * 180 / M_PI) - 90);
}

double DynamicEntity::get_dir() const { return direction; }

void DynamicEntity::set_speed(double new_speed) { speed = new_speed; }

double DynamicEntity::get_speed() const { return speed; }
