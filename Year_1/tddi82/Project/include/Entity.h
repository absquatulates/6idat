#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <memory>

struct AABB
{
int left;
int right;
int top;
int bottom;
};

using Hitbox = AABB;


class Entity
{
public:
    Entity();

    /**
     * @param pos spawn position
     * @param hb hitbox dimensions
    */
    Entity(std::pair<int,int> const & pos, Hitbox const & hb);

    virtual ~Entity();

    /* Renders Entitiy */
    virtual void render(sf::RenderTarget & target); 

    /* Returns position of Entity */
    std::pair<int, int> get_pos() const;

    /* Returns hitbox of Entity */
    Hitbox get_body() const;

    /* Checks if two hitboxes collide */
    bool collide (Entity const& other);

    /* Handles collision */
    virtual void handleCollide(Entity * other);

    /* Checks if Entity is alive */
    virtual bool isAlive();

    /* Updates Entity */
    virtual void update();

    /* Updates Entity */
    virtual void update(std::vector<std::shared_ptr<Entity>> & d_e_v);

    /* Checks if Entity is out of bounds */
    bool out_of_bounds();

    /* Returns type of Entity */
    virtual ENTITY_TYPE get_type() const;

protected:
    ENTITY_TYPE type{ENTITY_TYPE::STATIC_ENTITY};
    
    /* Graphical representation of Entity */
    std::pair<int, int> pos;
    Hitbox body;
    sf::Sprite sprite{};
    sf::Texture texture{};
    
};

#endif //ENTITY_H