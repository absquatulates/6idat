#ifndef REGISTER_H
#define REGISTER_H

#include "hero.h"
#include <iomanip>

using Register_Type = std::vector<Hero_Type>;

void read(std::ifstream& file, Register_Type& heroes);

//addHero
Hero_Type inputHero();
bool matchName(Hero_Type const& newHero, Register_Type const& heroes);
void writeToFile(Hero_Type const& newHero, Register_Type & heroes, std::string const& filename);
void addHero(Register_Type & heroes, std::string const& filename);

//findMatchingHeroes
Register_Type makeMatchList(Register_Type const& heroes, std::vector<int> const& newinterests);
void printHeroes(Register_Type const& heroes);
std::vector<int> getinterests();
Register_Type removeDuplicates(Register_Type const& matchingHeroes);
void findMatchingHeroes(Register_Type const& heroes);




#endif
