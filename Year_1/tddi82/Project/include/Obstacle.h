#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Entity.h"
#include "Constants.h"

#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <utility>

class Obstacle : public Entity
{
public:
    /**
     * @param pos spawn position
     * @param hb hitbox dimensions
     * @param obstacleType type of obstacle
     */
    Obstacle(std::pair<int,int> const & pos, Hitbox const & hb, ENTITY_TYPE obstacleType);
};
#endif