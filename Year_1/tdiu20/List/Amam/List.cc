#include "List.h"



//Konstruktorer
List::List()
{
    first = new Node{};
    last = new Node{};

    last->previous = first;
    last->next = nullptr;

    first->next = last;
    first->previous = nullptr;
}

List::List(std::initializer_list<int>const& list)
    : List()
{
    for(int value : list)
    {
        insert(value);
    }
}

List::List(List const& other)
    :List{}
{
    *this = other;
}

List::List(List && other)
    :List{}
{
    first = other.first;
    other.first = nullptr;

    last = other.last;
    other.last = nullptr;
}


List::~List()
{
    clear();
    delete first;
    delete last;
}

List& List::operator=(List const& other)
{
    clear();
    Node* tmp_node{other.first->next}; //pekar på första
    while (tmp_node != other.last)
    {
        insert(tmp_node->value);
        tmp_node = tmp_node->next;
    }
    return *this;
}

List& List::operator=(List && other)
{
    Node* tmp_node{first};
    first = other.first;
    other.first = tmp_node;

    tmp_node = last;
    last = other.last;
    other.last = tmp_node;

    return *this;
}


void List::insert(int new_value)
{
    Node* new_node = new Node;
    new_node->value = new_value;
    Node* tmp_node = first; //pekar på sentinell

    while((tmp_node->next != nullptr))
    {
        if (tmp_node->value > new_value)
        {
            break;
        }    
        tmp_node = tmp_node->next;
    }
    new_node->next = tmp_node;
    new_node->previous = tmp_node->previous;
    tmp_node->previous->next = new_node;
    tmp_node->previous = new_node;
}

int List::size() const
{
    Node* tmp_node{first};
    int size{-1};

    while(tmp_node != last)
    {
        size++;
        tmp_node = tmp_node->next;
    }

    return size;
}

bool List::empty() const
{
    return first->next == last;
}

int List::at(int index) const
{
    Node* tmp_node{first};
    if ((index < 0) or index > size())
    {
        throw std::invalid_argument("Out of bounds");
    }
    for (int i{-1}; i < index; i++) // i{-1} för 0-indexering
    {
        tmp_node = tmp_node->next;
    }
    return tmp_node->value;
}

void List::remove(int index)
{
    Node* tmp_node{first}; //pekar på sentinell
    if ((index < 0) or (index > size()))
    {
        throw std::invalid_argument("Out of bounds");
    }
    for (int i{-1}; i < index; i++)
    {
        tmp_node=tmp_node->next;
    }
    tmp_node->previous->next = tmp_node->next;
    tmp_node->next->previous = tmp_node->previous;
    delete tmp_node;   
}

void List::clear()
{
    while (first->next != last)
    {
       remove(0);
    }
}

List List::copy() const
{
    List tmp_list;
    Node* tmp_node{first->next}; //pekar på första
    while (tmp_node != last)
    {
        tmp_list.insert(tmp_node->value);
        tmp_node = tmp_node->next;
    }
    return tmp_list;
}

std::string List::to_string() const
{   
    Node* tmp_node{first->next};
    std::string str{};
    while (tmp_node != last)
    {
        str.append(std::to_string(tmp_node->value));
        str.append(" ");
        tmp_node = tmp_node->next;
    }
    if (!(empty()))
    {
        str.pop_back();
    }
    
    return str;
}

std::ostream& operator<<(std::ostream& os, List const& rhs)
{
    os << rhs.to_string();
    return os;
}

List List::sub(std::initializer_list<int>const& list)
{
    Node* tmp_node{first};
    List sub_list{};
    int index {-1};
    int lastValue{0};
    for(int value : list)
    {   
        if ((value < lastValue) or (value > (size()-1)))
        {
            throw std::invalid_argument("Bad sub!");
        }
        while (index != value)
        {
            tmp_node = tmp_node->next;
            index++;
        }
        lastValue = value;
        sub_list.insert_at_end(tmp_node->value);
    }
    return sub_list;
}

void List::insert_at_end(int new_value)
{
    Node* new_node = new Node;
    new_node->value = new_value;
    Node* tmp_node = last;
    new_node->next = tmp_node;
    new_node->previous = tmp_node->previous;
    tmp_node->previous->next = new_node;
    tmp_node->previous = new_node;
}

