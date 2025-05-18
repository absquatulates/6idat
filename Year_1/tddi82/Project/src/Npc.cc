#include "Npc.h"

#include <cmath>
#include <random>

Npc::Npc(std::pair<int,int> const & pos, ShipType const stype)
    :   Ship{pos, Hitbox{40, 40, 70, 70}, 20, 0.2, 10, 0, stype}, patrol_pos{new_patrol_pos()}
{
    type = NPC;
    
    
}

void Npc::update()
{
    patrol();
    DynamicEntity::update();
}

void Npc::handleCollide(Entity * other)
{
    if (dynamic_cast<Enemy*>(other) != nullptr)
    {
        health -= 1;
    }
}



void Npc::patrol()
{
    int npc_x{get_pos().first};
    int npc_y{get_pos().second};
    if (sqrt(pow(patrol_pos.first - npc_x, 2) + pow(patrol_pos.second - npc_y, 2)) <= 100)
    { 
        patrol_pos = new_patrol_pos();
    }
    double angle{atan2((patrol_pos.second - npc_y),(patrol_pos.first - npc_x))};
    direction = angle;
    move(forward);
}

std::pair<int, int> Npc::new_patrol_pos()
{
    std::random_device rd;
    return {rd() % WIDTH, rd() % HEIGHT};
}
