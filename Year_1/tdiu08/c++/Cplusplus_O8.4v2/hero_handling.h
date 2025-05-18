#ifndef HERO_HANDLING_H
#define HERO_HANDLING_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include "register_handling.h"

// #include "register_handling.h"
// #include "hero_handling.h"

struct register_handling;

struct hero_type
{
  std::string name{""};
  int age{};
  double weight{};
  std::string hair_color{};
  std::vector<int> intrests;

  std::string toString() const;
};

#endif