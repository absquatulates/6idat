#ifndef NPC_SHOOTER_H
#define NPC_SHOOTER_H

#include "Game_State.h"
#include "Ship.h"


class Enemy;

class Npc_Shooter : public Ship
{
public:
    /**
     * @param pos spawn position
     * @param player reference to player ship
    */
    Npc_Shooter(std::pair<int,int> const & pos, ShipType const stype, std::vector<std::shared_ptr<Entity>>& e);

    /**
     * @param entity_v EntityVector so Enemy can spawn canonballs
    */
    void update(std::vector<std::shared_ptr<Entity>> & entity_v) override;
    
    /**
     * handles collision with other entity
     * @param other entity collided with
    */
    void handleCollide(Entity * other) override; 

private:
    static constexpr double radius{300};
    int firerate{};
    std::vector<std::shared_ptr<Entity>>& entities;
    std::shared_ptr<Enemy> enemy;

    /**
     * @return true if player is within radius of enemy
    */
    bool inside_radius(double const r) const;


    void target(std::pair<int, int> const& pos);

    

    

};

#endif