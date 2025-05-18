#include "Object.h"

Player::Player(Point pos, int hp)
    : Object{pos}, hp{hp}
{}

bool Enemy::collide(Object* o)
{
    Player* p{dynamic_cast<Player*>(o)};
    if (p != nullptr)
    {
        p->hit();
    }

    Enemy* e{dynamic_cast<Enemy*>(o)};
    
}