//polygon.h
#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>
#include <sstream>


class Polygon
{
public:
    Polygon(int side_length, std::vector<int> side_length_vector);
    Polygon(std::initializer_list<int> & vector);
    std::string to_string();


    Polygon operator+=(int const rhs);
    Polygon operator+(int const rhs);

private:

    int side_length{};
    std::vector<int> side_length_vector;
    
};

std::ostream& operator<<(std::ostream& os, Polygon const& other);

//operator+(int const lhs, Polygon const& rhs);

#endif
