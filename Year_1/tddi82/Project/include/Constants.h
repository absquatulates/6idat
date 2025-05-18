#ifndef CONSTANTS_H
#define CONSTANTS_H

int const WIDTH{1280};
int const HEIGHT{720};

double const FPS{60.0};

enum ENTITY_TYPE
{   
    STATIC_ENTITY,
    SHIP_WRECK,
    ISLAND,
    PLAYER,
    ENEMY,
    CANNONBALL,
    POWER_UP,
    NPC,
    NPC_SHOOTER
};



#endif //CONSTANTS_H