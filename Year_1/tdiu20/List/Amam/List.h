#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <sstream> 


class List
{
public:
    List();
    List(std::initializer_list<int> const& list);
    List(List const& other);
    List(List && other);

    ~List();
    List& operator=(List const& other);
    List& operator=(List && other);

    void insert(int val);//klar
    int size() const;//klar
    bool empty() const;//klar
    int at(int index) const;//klar
    void remove(int index);//klar
    void clear(); //klar
    List copy() const; //klar
    std::string to_string() const; //klar
    //void print();
    List sub(std::initializer_list<int>const& list);

private:

    void insert_at_end(int val);

    struct Node
    {
        int value;
        Node* next;
        Node* previous;
    };

    Node* first{};
    Node* last{};
};

std::ostream& operator<<(std::ostream& os, List const& rhs);

#endif