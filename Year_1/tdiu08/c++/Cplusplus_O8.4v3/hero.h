#ifndef HERO_H
#define HERO_H

#include <string>
#include <vector>
#include <ostream>
#include <iomanip>

struct Hero_Type
{
    std::string name{};
    int year{};
    double weight{};
    std::string haircolor{};
    std::vector<int> interests{};
};

bool operator<(Hero_Type const &lhs, Hero_Type const &rhs);

std::ostream &operator<<(std::ostream &os, Hero_Type const &hero);

#endif