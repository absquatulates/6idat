#ifndef HERO_HANDLING_H
#define HERO_HANDLING_H

#include <string>
#include <vector>

struct hero_type
{
    std::string name {""};
    int age {};
    double weight {};
    std::string hair_color {""};
    std::vector<int> intrests;  
};


#endif