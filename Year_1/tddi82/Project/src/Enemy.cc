#include "Enemy.h"

#include <cmath>
#include <random>

Enemy::Enemy(std::pair<int,int> const & pos, Ship & player, ShipType const stype)
    :   Ship{pos, Hitbox{40, 40, 70, 70}, 20, 0.2, 5, 1, stype}, player{player}
{
    type = ENEMY;
    if (stype == ENEMY_SEEKER) speed = speed * 2;
    else if (stype == ENEMY_TANKER) health = health * 2;
}



void Enemy::update(std::vector<std::shared_ptr<Entity>> & entity_v)
{
    if (inside_radius(radius))
    {
        if (firerate <= 0) 
        {
            shoot(entity_v);
            firerate = 100;
        }
        hunt(player.get_pos());
        patrol_pos = new_patrol_pos();
    }
    else
    {
        patrol();
    }
    firerate--;
    DynamicEntity::update();
}

bool Enemy::inside_radius(double const r) const
{
    int x_dist{player.get_pos().first - get_pos().first};
    int y_dist{player.get_pos().second - get_pos().second};
    double dist{sqrt(pow(x_dist, 2) + pow(y_dist, 2))};
    return r > dist;
}

void Enemy::hunt(std::pair<int, int> const& pos)
{
    int enemy_x{get_pos().first};
    int enemy_y{get_pos().second};
    double angle{atan2((pos.second - enemy_y),(pos.first - enemy_x))};

    direction = angle;
    if (inside_radius(100)) move(back);
    else move(forward);
}

void Enemy::patrol()
{
    if (sqrt(pow(patrol_pos.first - get_pos().first, 2) + 
             pow(patrol_pos.second - get_pos().second, 2)) <= 50)
    { 
        patrol_pos = new_patrol_pos();
    }
    hunt(patrol_pos);
}

std::pair<int, int> Enemy::new_patrol_pos()
{
    std::random_device rd;
    return {rd() % WIDTH, rd() % HEIGHT};
}



