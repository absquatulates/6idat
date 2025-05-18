#ifndef SHIP_H
#define SHIP_H

#include "DynamicEntity.h"
#include "Canonball.h"

enum ShipType
{
    PLAYER_SHIP,
    ENEMY_TANKER,
    ENEMY_SEEKER,
    NPC_SHIP,
    NPC_SHOOTER_SHIP
};

/**
 * Class representing a ship
*/
class Ship : public DynamicEntity
{
public:
    /**
     * @param pos spawn position
     * @param hb hitbox dimensions
     * @param dir direction
     * @param speed inital speed
     * @param hp hitpoints
     * @param dmg damage
     * @param type type of ship
    */
    Ship(std::pair<int,int> const & pos, Hitbox const & hb, 
         double const dir, double const speed, int const hp, int const dmg, ShipType type);

    virtual ~Ship() = default;

    /**
     * @returns health
    */
    int get_health() const;
    
    /**
     * lowers health by dmg
     * @param dmg how mouch damage ship will take
    */
    void hit(int const dmg);
    
    /**
     * sets health to hp
     * @param hp new health
    */
    void set_health(int const hp);

    /**
     * sets shielded to s
     * @param s new shield value
    */
    void set_shield(bool s);

    /**
     * @returns true if ship is shielded
    */
    bool get_shield() const;

    /**
     * shoots a projectile
    */
    void shoot(std::vector<std::shared_ptr<Entity>> & d_e_v);

    /**
     * handles collision with other entity
     * @param other entity collided with
    */
    void handleCollide(Entity * other) override;

    /**
     * @returns true if ship is alive
    */
    bool isAlive() override;

protected:
    int health; //hitpoints ship has left
    int damage; //damage when shooting
    bool shielded{false};
};

#endif