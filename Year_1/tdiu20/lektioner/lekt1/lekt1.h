#ifndef LEKT1_H
#define LEKT1_H

#include <string>

class Book
{
public:
    Book(std::string const& t, std::string const& g, std::string const& a, int p, std::string const& s, int y);
    int get_year();
    std::string get_genre();

    bool operator>(Book const& rhs);

private:
    
    std::string title{""};
    std::string genre{""};
    std::string author{""};
    int number_of_pages{};
    std::string status{""};
    int year{};
    


};


#endif