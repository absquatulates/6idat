#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <iterator>

class List
{
public:
    List();
    ~List();
    List(List const &);
    List(List &&) noexcept;
    List(std::initializer_list<int>);

    List & operator=(List const &)&;
    List & operator=(List &&)& noexcept;

    void push_front(int);
    void push_back(int);

    int back() const noexcept;
    int & back() noexcept;

    int front() const noexcept;
    int & front() noexcept;

    int & at(int idx);
    int const & at(int idx) const;

    int size() const noexcept;
    bool empty() const noexcept;

    void swap(List & other) noexcept;

    
    
private:

struct Node
{
    Node();

    Node(int v, Node* p, std::unique_ptr<Node> n);
    
    Node(Node const& other) = delete;
    Node& operator=(Node const& other) = delete;

    int value {};
    Node * prev {};
    std::unique_ptr<Node> next;
};

class List_Iterator
{
public:

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;
    using value_type = int;
    using pointer = int*;
    using reference = int&;

    List_Iterator(Node* ptr);
    reference operator*() const;
    pointer operator->();
    List_Iterator& operator++();
    List_Iterator& operator++(int);
    List_Iterator& operator--();
    List_Iterator& operator--(int);

    bool operator==(List_Iterator const& rhs) const;
    bool operator!=(List_Iterator const& rhs) const;

private:
    Node* m_ptr;
};

    std::unique_ptr<Node> head;
    Node * tail;
    int sz;

    
};

#endif //LIST_H
