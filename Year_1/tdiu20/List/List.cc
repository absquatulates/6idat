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
    Node* temp{first};
    int size{-1};

    while(temp != last)
    {
        size++;
        temp = temp->next;
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
    for (int i{-1}; i < index; i++) // i{-1} för 0-indexering
    {
        tmp_node = tmp_node->next;
    }
    return tmp_node->value;
}

void List::remove(int val)
{
    Node* tmp_node = first; //pekar på sentinell
    for (int i{-1}; i < val; i++)
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

List List::copy()
{
    List tmp_list;
    Node* tmp_node = first; //pekar på sentinell
    tmp_node = tmp_node->next;
    while (tmp_node != last)
    {
        tmp_list.insert(tmp_node->value);
        tmp_node = tmp_node->next;
    }
    return tmp_list;
}


std::string List::to_string()
{
    Node* tmp_node = first->next;   
    std::string str{};
    while (tmp_node != last)
    {
        str.append(std::to_string(tmp_node->value));
        tmp_node = tmp_node->next;
    }
    return str;
}


List List::sub(std::initializer_list<int>const& list)
{
    Node* tmp_node{first};
    List sub_list{};
    int index {-1};
    for(int value : list)
    {
        while (index != value)
        {
            tmp_node = tmp_node->next;
            index++;
        }
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