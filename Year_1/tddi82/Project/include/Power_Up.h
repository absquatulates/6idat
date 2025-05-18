#ifndef POWER_UP_H
#define POWER_UP_H

#include "Constants.h"
#include "Entity.h"
#include "Ship.h"
#include <string>
#include <utility>


class Power_Up : public Entity
{
public:
    Power_Up(std::pair<int, int> const& p, int const d, Ship& player);
    virtual ~Power_Up() = default;

    std::pair<int, int> get_position() const;
    void set_position(std::pair<int, int> const& p);

    //std::string get_type() const;
    
    int get_duration() const;
    void decrease_duration();

    virtual void apply_effect(Ship& player) = 0;

    void handleCollide(Entity * other) override;

    bool isAlive() override;

    void update() override;

protected:
    int duration;
    Ship& player;
    bool did_hit;
};

class Speed_Up : public Power_Up
{
public:
    Speed_Up(Ship& player);
    void apply_effect(Ship& player) override;
    void update() override;
    
};

class Shield : public Power_Up
{
public:
    Shield(Ship& player);
    void apply_effect(Ship& player) override;
    void update() override;
};

/*
never implemented
class Double_Value : public Power_Up
{
public:
    Double_Value(int const d, Ship& player);
    void apply_effect(Ship& player) override;
};
*/


class Heal : public Power_Up
{
public:
    Heal(int const d, Ship& player);
    void apply_effect(Ship& player) override;
};



#endif // POWER_UP_H