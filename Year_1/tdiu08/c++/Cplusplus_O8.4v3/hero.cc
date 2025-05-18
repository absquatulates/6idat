#include "hero.h"


bool operator<(Hero_Type const& lhs, Hero_Type const& rhs)
{
    return lhs.name < rhs.name;
}


std::ostream& operator<<(std::ostream& os, Hero_Type const& hero)
{
  os << std::left << std::setw(11) << hero.name << std::left << 
        std::setw(12) << hero.year << std::left << std::setw(8) << 
        std::fixed << std::setprecision(2) << hero.weight << 
        std::left << std::setw(12) << hero.haircolor;

  for (int i{}; i < hero.interests.size(); i++)
  {
      os << std::right << std::setw(3) << hero.interests.at(i);
  }
  return os;
  
}

