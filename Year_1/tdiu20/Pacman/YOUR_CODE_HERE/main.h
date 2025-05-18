#ifndef MAIN_H
#define MAIN_H

#include "ghost.h"
#include "given.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
class Ghost_Tester
{
public:
    Ghost_Tester();
    void run();
    std::vector<Ghost*> ghosts {} ; 
    
private:
    std::string to_draw(Point const& curr_pos, std::vector<Ghost*> ghosts);
    void draw_map();
    bool scatter{};
    Pacman pacman{};
};


#endif