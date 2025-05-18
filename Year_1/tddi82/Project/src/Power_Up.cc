#include "../include/Power_Up.h"
#include "../include/Player.h"

#include <iostream>

Power_Up::Power_Up(std::pair<int, int> const& p, int const d, Ship& player)
    :   Entity{p, Hitbox{20,20,20,20}}, duration{d}, player{player}, did_hit{false}
{
    texture.loadFromFile("resources/Powerup.png");
     sprite.setTexture(texture);

    /* Set sprite origin to center of sprite texture */
    sprite.setOrigin(sprite.getLocalBounds().width / 2,
                     sprite.getLocalBounds().height / 2);
    sprite.setScale(0.2, 0.2);
    type = POWER_UP;
}

std::pair<int, int> Power_Up::get_position() const
{
    return pos;
}

void Power_Up::set_position(std::pair<int, int> const& p)
{
    if (p.first < 0 or p.first > WIDTH or p.second < 0 or p.second > HEIGHT)
    {
        throw std::runtime_error("position outside valid range");
    }
    pos = p;
}

int Power_Up::get_duration() const
{
    return duration;
}

void Power_Up::decrease_duration()
{
    --duration;
}



void Power_Up::handleCollide(Entity * other)
{
    if (dynamic_cast<Player*>(other) != nullptr && isAlive())
    {
        did_hit = true;
        texture.loadFromFile("resources/Empty.png");
    }
    
}

bool Power_Up::isAlive()
{
    return duration > 0;
}

void Power_Up::update()
{
    if (isAlive() && did_hit)
    {
        apply_effect(player);
        decrease_duration();
    }
    
    
}

/*===================================================
                    Speed_Up
===================================================*/
Speed_Up::Speed_Up(Ship& player)
    : Power_Up{std::make_pair(300, 50), 300, player}
{

}

void Speed_Up::apply_effect(Ship& player)
{
    player.set_speed(1.5);
    if (duration == 1)
    {
        player.set_speed(1.0);
    }
}

void Speed_Up::update()
{
    if (did_hit)
    {
        apply_effect(player);
        decrease_duration();
    }
    if (duration == 1)
    {
        player.set_speed(1.0);  
    }
}

/*===================================================
                    Shield
===================================================*/
Shield::Shield(Ship& player)
    : Power_Up{std::make_pair(1000, 300), 500, player}
{

}

void Shield::apply_effect(Ship& player)
{
    if (!player.get_shield() && duration > 10) std::cout << "now shielded" << std::endl;
    player.set_shield(true);
}

void Shield::update()
{
    if (did_hit)
    {
        apply_effect(player);
        decrease_duration();
    }
    if (duration == 1)
    {
        std::cout << "shield off" << std::endl;
        player.set_shield(false);
    }
}


/*===================================================
                    Double_Value
===================================================*/
//value was never implemented in game som power up was never used
/*Double_Value::Double_Value(int const d, Ship& player)
    : Power_Up{std::make_pair(37, 900), d, player}
{

}

void Double_Value::apply_effect(Ship& player)
{}*/

/*===================================================
                    Heal
===================================================*/
//doesnt want to spawn for some reason so wont be included in game_state
Heal::Heal(int const d, Ship& player)
    : Power_Up{std::make_pair(100, 500), d, player}
{

}

void Heal::apply_effect(Ship& player)
{
    player.set_health(10); //max health
}

