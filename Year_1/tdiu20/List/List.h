#ifndef LIST_H
#define LIST_H

#include <iostream>


class List
{
public:

    List(std::initializer_list<int> const& list);
    List();

    std::string to_string();            //
    int at(int index) const;            //
    void remove(int val);               //
    //int same_value(int val);                 //Behövs den?
    void clear();                       //
    int size() const;                   //
    void insert(int val);               //
    //int index(int const value) const;        //Behövs den?
    bool empty() const;                 //
    void print();
    List copy();                        //     Hur testa?

    //Bonus
    void insert_at_end(int new_value);
    List sub(std::initializer_list<int>const& list);

private:

    void sort_list();

    struct Node
    {
        int value;
        Node* next;
        Node* previous;
    };

    Node* first{};
    Node* last{};

};


#endif