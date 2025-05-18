#ifndef REGISTER_HANDLING_H
#define REGISTER_HANDLING_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include "hero_handling.h"

struct hero_type;
struct register_type
{
  std::vector<hero_type> hero_list;
};

void readfile(std::ifstream &infile, register_type &heroes);
void saveToFile(std::string &filepath, register_type &heroes);
void add_hero(std::string &filepath, register_type &heroes);
bool compareFirstLetter(const hero_type &hero1, const hero_type &hero2);

#endif