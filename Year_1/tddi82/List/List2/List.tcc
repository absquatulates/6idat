#include "List.h"
#include <iterator>
#include <utility>
#include <stdexcept>
#include <string>

namespace List_NS
{
    template <typename T>
    List<T>::List()
        : head{ std::make_unique<Node>() }, tail{}, sz{}
    {
        head->next = std::make_unique<Node>(T{}, head.get(), nullptr) ;
        tail = head->next.get();
    }

    template <typename T>
    List<T>::~List()
    {}

    template <typename T>
    List<T>::List(List const & other)
        : List{}
    {
        for (Node * tmp {other.head->next.get()}; tmp != other.tail ; )
        {
            push_back(tmp->value);
            tmp = tmp->next.get();
        }
    }

    template <typename T>
    List<T>::List(List && tmp) noexcept
        :List{}
    {
        swap(tmp);
    }

    template <typename T>
    List<T>::List(std::initializer_list<T> lst)
        : List{}
    {
        for ( auto val : lst )
        {
            push_back(val);
        }
    }

    template <typename T>
    void List<T>::push_front(T value)
    {
        Node * old_first { head->next.get() };
        head->next = std::move
        (std::make_unique<Node>(value, head.get(), std::move(head->next)));
        old_first->prev = head->next.get();
        ++sz;
    }

    template <typename T>
    void List<T>::push_back(T value)
    {
        Node * old_last { tail->prev };
        old_last->next = std::make_unique<Node>(value, old_last, std::move(old_last->next));
        tail->prev = old_last->next.get();
        ++sz;
    }

    template <typename T>
    bool List<T>::empty() const noexcept
    {
        return head->next.get() == tail;
    }

    template <typename T>
    T List<T>::back() const noexcept
    {
        return tail->prev->value;
    }

    template <typename T>
    T& List<T>::back() noexcept
    {
        return tail->prev->value;
    }

    template <typename T>
    T List<T>::front() const noexcept
    {
        return head->next->value;
    }

    template <typename T>
    T& List<T>::front() noexcept
    {
        return head->next->value;
    }

    template <typename T>
    T& List<T>::at(int idx)
    {
        return const_cast<T &>(static_cast<List const *>(this)->at(idx));
    }
    template <typename T>
    T const & List<T>::at(int idx) const
    {
        if (idx >= sz)
            throw std::out_of_range{"Index not found"};
        Node * tmp {head->next.get()};
        while ( idx > 0 )
        {
            tmp = tmp->next.get();
            --idx;
        }
        return tmp->value;
    }

    template <typename T>
    int List<T>::size() const noexcept
    {
        return sz;
    }
    template <typename T>
    void List<T>::swap(List & other) noexcept
    {
        using std::swap;
        swap(head, other.head);
        swap(tail, other.tail);
        swap(sz, other.sz);
    }

    template <typename T>
    List<T> & List<T>::operator=(List const & rhs) &
    {
        List{rhs}.swap(*this);
        return *this;
    }

    template <typename T>
    List<T> & List<T>::operator=(List && rhs)& noexcept
    {
        swap(rhs);
        return *this;
    }

    //Node

    template <typename T>
    List<T>::Node::Node()
        :value{}, prev{}, next{}
    {

    }

    template <typename T>
    List<T>::Node::Node(T v, Node* p, std::unique_ptr<Node> n)
        : value{v}, prev{p}, next{std::move(n)} 
    {}

    //Iterator Funktions
    template <typename T>
    List<T>::List_Iterator::List_Iterator(Node* ptr)
        :m_ptr{ptr}
    {}

    template <typename T>
    typename List<T>::List_Iterator::reference List<T>::List_Iterator::operator*() const
    { 
        return m_ptr->value;
    }

    template <typename T>
    typename List<T>::List_Iterator::pointer List<T>::List_Iterator::operator->() 
    { 
        return &m_ptr->value;
    }

    template <typename T>
    typename List<T>::List_Iterator& List<T>::List_Iterator::operator++() //PRE
    {
        if(m_ptr->next.get() != nullptr)
        {
            m_ptr = m_ptr->next.get();
        }
        return *this;
    }

    template <typename T>
    typename List<T>::List_Iterator List<T>::List_Iterator::operator++(int) //POST
    {
        List_Iterator tmp{*this};
        ++*this;
        return tmp;
    }

    template <typename T>
    typename List<T>::List_Iterator& List<T>::List_Iterator::operator--() //PRE
    {
        if(m_ptr->prev->prev != nullptr)
        {
            m_ptr = m_ptr->prev;
        }
        return *this;
    }

    template <typename T>
    typename List<T>::List_Iterator List<T>::List_Iterator::operator--(int) //POST
    {
        List_Iterator tmp{*this};
        --*this;
        return tmp;
    }

    template <typename T>
    bool List<T>::List_Iterator::operator==(List_Iterator const& rhs) const
    {
        return (m_ptr == rhs.m_ptr);
    }

    template <typename T>
    bool List<T>::List_Iterator::operator!=(List_Iterator const& rhs) const
    {
        return !(*this == rhs);
    }

    template <typename T>
    typename List<T>::List_Iterator List<T>::begin() const
    {
        return List_Iterator {head->next.get()};

    }

    template <typename T>
    typename List<T>::List_Iterator List<T>::end() const
    {
        return List_Iterator {tail};
    }
    
}


