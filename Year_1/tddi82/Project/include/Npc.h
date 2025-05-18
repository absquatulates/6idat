#ifndef NPC_H
#define NPC_H

#include "Game_State.h"
#include "Ship.h"

class Npc : public Ship
{
public:
    /**
     * @param pos spawn position
     * @param player reference to player ship
    */
    Npc(std::pair<int,int> const & pos, ShipType const stype);

    /**
     * @param entity_v EntityVector so Enemy can spawn canonballs
    */
    void update() override;
    
    /**
     * handles collision with other entity
     * @param other entity collided with
    */
    void handleCollide(Entity * other) override; 

private:
    
    std::pair<int, int> patrol_pos;

    /**
     * Enemy will move in a random direction
    */
    void patrol();

    /**
     * @return new patrol position
    */
    std::pair<int, int> new_patrol_pos();
};

#endif