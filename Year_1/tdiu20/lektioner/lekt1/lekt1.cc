#include "lekt1.h"

#include <iostream>
#include <string>

using namespace std;

Book::Book(string const& t, string const& g, string const& a, int p, string const& s, int y)
    : title{t}, genre{g}, author{a}, number_of_pages{p}, status{s}, year{y}
{}

int Book::get_year()
{
    return year;
}

string Book::get_genre()
{
    return genre;
}

bool operator>(Book const& rhs)
{

}