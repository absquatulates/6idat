#include "Ship.h"
#include "Power_Up.h"

#include <cmath>
#include <memory>

Ship::Ship(std::pair<int, int> const& pos, Hitbox const& hb, double const dir,
           double const speed, int const hp, int const dmg, ShipType type)
    : DynamicEntity{pos, hb, dir, speed}, health{hp}, damage{dmg} {
    if (type == PLAYER_SHIP) {
        texture.loadFromFile("resources/player.png");
    } else if (type == ENEMY_TANKER) {
        texture.loadFromFile("resources/tanker.png");
    } else if (type == ENEMY_SEEKER) {
        texture.loadFromFile("resources/seeker.png");
    } else if (type == NPC_SHIP) {
        texture.loadFromFile("resources/npc.png");
    } else if (type == NPC_SHOOTER_SHIP) {
        texture.loadFromFile("resources/npc.png");
    }


    sprite.setTexture(texture);

    /* Set sprite origin to center of sprite texture */
    sprite.setOrigin(sprite.getLocalBounds().width / 2,
                     sprite.getLocalBounds().height / 2);

    /* Since texture is facing down, rotate 90 degrees to match direction */
    sprite.setRotation(-90);
}

int Ship::get_health() const { return health; }

void Ship::hit(int const dmg) {

    if (!shielded) {
        velocity.first /= 2;
        velocity.second /= 2;
        health -= dmg;
    }
}

void Ship::shoot(std::vector<std::shared_ptr<Entity>> & d_e_v)
{
    // Cannonball offset
    std::pair<int, int> spawnpos{get_pos().first + 90 * std::cos(get_dir()),
                                 get_pos().second + 90 * std::sin(get_dir())};
    d_e_v.push_back(std::make_shared<Cannonball>(spawnpos, get_dir(), 15, damage));
}

void Ship::set_health(int const hp) { health = hp; }

void Ship::set_shield(bool s) { shielded = s; }

bool Ship::get_shield() const { return shielded; }

void Ship::handleCollide(Entity* other) 
{ 
    if (dynamic_cast<Ship*>(other) != nullptr)
    {
        velocity.first = -(velocity.first/4);
        velocity.second = -(velocity.second/4);
    }
    else if (dynamic_cast<Power_Up*>(other) == nullptr)
    {
        velocity.first /= 2;
        velocity.second /= 2;
    }
}

bool Ship::isAlive() {
    if (health <= 0) {
        return false;
    }
    return true;
}
