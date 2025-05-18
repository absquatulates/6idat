#ifndef ENEMY_H
#define ENEMY_H

#include "Game_State.h"
#include "Ship.h"

class Enemy : public Ship
{
public:
    /**
     * @param pos spawn position
     * @param player reference to player ship
    */
    Enemy(std::pair<int,int> const & pos,
          Ship & player, ShipType const stype);

    
    /**
     * @param entity_v EntityVector so Enemy can spawn canonballs
    */
    void update(std::vector<std::shared_ptr<Entity>> & entity_v) override;
    
    /**
     * @return reference to ship managed by Enemy object for rendering
    */

private:
    Ship & player;
    static constexpr double radius{300};
    int firerate{};
    std::pair<int, int> patrol_pos{player.get_pos()};

    /**
     * @return true if player is within radius of enemy
    */
    bool inside_radius(double const r) const;

    /**
     * Enemy will move towards player
    */
    void hunt(std::pair<int, int> const& pos);

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