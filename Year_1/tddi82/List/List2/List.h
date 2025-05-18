#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <iterator>

namespace List_NS
{
    template <typename T>
    class List
    {
    public:
        List<T>();
        ~List();
        List(List const &);
        List(List &&) noexcept;
        List(std::initializer_list<T>);

        List & operator=(List const &)&;
        List & operator=(List &&)& noexcept;

        void push_front(T);
        void push_back(T);

        T back() const noexcept;
        T & back() noexcept;

        T front() const noexcept;
        T & front() noexcept;

        T & at(int idx);
        T const & at(int idx) const;

        int size() const noexcept;
        bool empty() const noexcept;

        void swap(List & other) noexcept;
        
    private:
        struct Node
        {
            Node(); 

            Node(T v, Node* p, std::unique_ptr<Node> n);
            
            Node(Node const& other) = delete;
            Node& operator=(Node const& other) = delete;

            T value;
            Node * prev {};
            std::unique_ptr<Node> next;
        };
        std::unique_ptr<Node> head;
        Node * tail;
        int sz;


        class List_Iterator 
        {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type = T;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

            List_Iterator(Node* ptr);

            reference operator*() const;
            pointer operator->();

            List_Iterator& operator++();
            List_Iterator operator++(int);
    
            List_Iterator& operator--();
            List_Iterator operator--(int);

            bool operator==(List_Iterator const& rhs) const;
            bool operator!=(List_Iterator const& rhs) const;

        private:    
            Node* m_ptr;
        }; 
    public:
        List_Iterator begin() const;
        List_Iterator end() const;
    };
}



#include "List.tcc"
#endif //LIST_H
