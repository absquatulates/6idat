#ifndef CANNONBALL_H
#define CANNONBALL_H
#include "DynamicEntity.h"
#include "Ship.h"

class Cannonball : public DynamicEntity
{
public:
    /**
     * @param pos spawn position
     * @param dir direction
     * @param speed inital speed
     * @param dmg damage
     */
    Cannonball(std::pair<int,int> const & pos, double const dir, 
               double const speed, int const dmg);

    /**
     * @param other entity that was hit
    */
    void handleCollide(Entity * other) override;

    /**
     * @return true if cannonball is still alive
    */
    bool isAlive() override;

    /**
     * updates position based on velocity
    */
    void update() override;

private:
    int damage;
    bool didHit{false};
};

#endif