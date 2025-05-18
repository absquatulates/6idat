#include "deck.h"

Deck::Deck()
    : cards {}
{
    for (int i{1}; i <= 13; ++i)
    {
        cards.push_back(Card{"hearts",      i});
        cards.push_back(Card{"clubs",       i});
        cards.push_back(Card{"diamonds",    i});
        cards.push_back(Card{"spades",      i});
    }
}

void Deck::shuffle()
{
    //Lämna som övning till läaseren
}

bool Deck::is_empty() const
{
    return cards.empty();
}

Card Deck::draw()
{
    Card tmp { cards.back() };
    cards.pop_back();
    return tmp;
}

Card Deck::operator[](int index) const
{
    return cards.at(index);
}