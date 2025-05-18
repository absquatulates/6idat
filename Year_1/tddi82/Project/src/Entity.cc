#include "Entity.h"


Entity::Entity() : pos{0, 0}, body{0, 0, 0, 0} {}

Entity::Entity(std::pair<int, int> const& pos, Hitbox const& hb)
    : pos{pos}, body{hb} {
    /* Shape position based on pos passed */
    sprite.setPosition(sf::Vector2f(pos.first, pos.second));
}

Entity::~Entity() {}

void Entity::render(sf::RenderTarget& target) { target.draw(sprite); }

std::pair<int, int> Entity::get_pos() const { return pos; }

Hitbox Entity::get_body() const { return body; }

bool Entity::collide(Entity const& other) {
    return  (pos.first < other.get_pos().first + other.get_body().bottom
            && pos.first + body.bottom > other.get_pos().first
            && pos.second < other.get_pos().second + other.get_body().right
            && pos.second + body.right > other.get_pos().second);
}

bool Entity::isAlive() { return true; }

bool Entity::out_of_bounds() {
    /* Check if sprite is out of bounds */
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();

    if (spriteBounds.left >= 0 && spriteBounds.top >= 0 &&
        spriteBounds.left + spriteBounds.width <= WIDTH &&
        spriteBounds.top + spriteBounds.height <= HEIGHT) {
        return true;
    }
    return false;
}

/* Useless piece of shits */
void Entity::handleCollide(Entity* other) 
{
    (void)other; //Entity* other unused, removes warning
}

void Entity::update() {}

ENTITY_TYPE Entity::get_type() const { return type; }
void Entity::update(std::vector<std::shared_ptr<Entity>>& d_e_v) 
{
    (void)d_e_v; //d_e_v unused, removes warning
}
