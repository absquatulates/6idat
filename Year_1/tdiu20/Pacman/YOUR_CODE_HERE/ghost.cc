#include "ghost.h"
#include "given.h"
#include <cmath>


Ghost::Ghost(Pacman& pacman, const Point& pos, const Point& scatter_pos, const std::string& color)
    : pacman{pacman}, pos{pos}, scatter_pos{scatter_pos}, color{color} 
{}


Clyde::Clyde(Pacman& pacman, const Point& pos, const Point& scatter_pos, const std::string& color, const int& dis)
    : Ghost{pacman, pos, scatter_pos, color}, dis{dis}
{}


std::string Ghost::get_color() const
{
    return color;
}

Point Ghost::get_position() const
{
    return pos;
}

void Ghost::set_position(Point& new_pos)
{
    pos = new_pos;
}

Point Ghost::get_scatter_point() const
{
    return scatter_pos;
}

Point Blinky::get_chase_point() const
{
    return pacman.get_position();
}

Point Clyde::get_chase_point() const
{
    int x_dif{abs((pacman.get_position().x) - (get_position().x))};
    int y_dif{abs((pacman.get_position().y) - (get_position().y))};
    double total_dif{sqrt(x_dif*x_dif)+(y_dif*y_dif)};

    if (total_dif <= dis)
    {
        return get_scatter_point();
    }
    else
    {
        return pacman.get_position();
    }
}

Point Pinky::get_chase_point() const {
    return {pacman.get_position().x + 2 * pacman.get_direction().x, pacman.get_position().y + 2 * pacman.get_direction().y};
}

void Blinky::set_angry(bool anger)
{
    angry = anger;
}

Point Blinky::get_scatter_point() const
{
    if(!angry)
    {
        return scatter_pos;
    }
    else
    {
        return pacman.get_position();
    }
}