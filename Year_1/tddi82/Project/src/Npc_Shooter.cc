#include "Npc_Shooter.h"

#include <cmath>
#include <random>


Npc_Shooter::Npc_Shooter(std::pair<int,int> const & pos, ShipType const stype, std::vector<std::shared_ptr<Entity>>& e)
    :   Ship{pos, Hitbox{40, 40, 70, 70}, 0, 0.2, 10, 1, stype}, entities{e}, enemy{nullptr}
{
    type = NPC_SHOOTER;
    
    
}

void Npc_Shooter::update(std::vector<std::shared_ptr<Entity>> & entity_v)
{
    
        for (auto & e : entities)
        {
            if (e->get_type() == ENEMY)
            {
                enemy = std::dynamic_pointer_cast<Enemy>(e);
                break;
                
            }
        }
        
        target(enemy->get_pos());
        if (inside_radius(radius))
        {
            if (firerate <= 0) 
            {
                shoot(entity_v);
                firerate = 100;
            }
        }

    firerate--;
    
    DynamicEntity::update();
}

bool Npc_Shooter::inside_radius(double const r) const
{
    int x_dist{enemy->get_pos().first - get_pos().first};
    int y_dist{enemy->get_pos().second - get_pos().second};
    double dist{sqrt(pow(x_dist, 2) + pow(y_dist, 2))};
    return r > dist;
}

void Npc_Shooter::handleCollide(Entity * other)
{
    if (dynamic_cast<Enemy*>(other) != nullptr)
    {
        health -= 1;
    }
}
void Npc_Shooter::target(std::pair<int, int> const& pos)
{
    int enemy_x{get_pos().first};
    int enemy_y{get_pos().second};
    double angle{atan2((pos.second - enemy_y),(pos.first - enemy_x))};

    direction = angle;

}


