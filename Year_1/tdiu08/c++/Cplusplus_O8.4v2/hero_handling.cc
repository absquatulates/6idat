#include "register_handling.h"

using namespace std;

ostream &operator<<(ostream &os, const hero_type &s)
{
    return (os << "Name: " << s.name << ", Age: " << s.age << ", Hair color: " << s.hair_color << std::endl);
}

std::string hero_type::toString() const
{
    stringstream ss;
    ss << (*this);
    return ss.str();
}
