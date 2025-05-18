#ifndef CARD_H
#define CARD_H
#include <string>

class Card
{
public:

    Card(std::string const& in_suit, int const in_value);

    std::string to_string() const;
    int get_value() const;

    bool Card::operator<(Card const& rhs) const;
    bool Card::operator>(Card const& rhs) const;

    Card& operator++();
    Card operator++(int);


private:
    int value;
    std::string suit;
};

std::ostream& operator<<(std::ostream& os, Card const& rhs);



#endif