#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <iterator>


// Information om komplettering: 
//   Kompletteringen kan gälla hela filen och alla filer i labben, 
//   så får ni komplettering på en sak, kan samma sak förekomma på 
//   fler ställen utan att jag skrivit det. 
// 
//   Komplettering lämnas in via sendlab efter senast en (1) vecka 
// 
//   Har ni frågor om kompletteringen kan ni maila mig på: 
//   edvin.dyremark@liu.se

// Komplettering: Eftersom listan nu kan innehålla vilken typ som helst ska vi undvika onödiga kopieringar. 
// Se över all er kod! (Det gäller även loopar, returtyper för medlemsfunktioner, konstruktorer) 
    //KLAR
// Komplettering: Användaren av listan ska ha tillgång till iteratorn.
// (Tänk även på att användaren endast ska kunna skapa en iterator genom listans funktioner begin() & end()
    //KLAR

// Komplettering: Node-structen ska definieras i .tcc filen och inte i .h filen.
    //KLAR

// Komplettering: Ni testar inte namespace.
    //KLAR

// Kommentar: difference_type är typen på avståndet mellan två iteratorer, och borde därför vara int eller ptrdiff_t. 

// Kommentar: att sätta const på begin och end är missvisande eftersom det med en iterator går att ändra på listan.  
    //KLAR

// Kommentar: Testa iteratorn för både framåt- och bakåtriktad iteration.

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
        List(std::initializer_list<T> const& lst);

        List & operator=(List const&)&;
        List & operator=(List &&)& noexcept;

        void push_front(T const& value);
        void push_back(T const& value);

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
        struct Node;

        std::unique_ptr<Node> head;
        Node * tail;
        int sz;


        class List_Iterator 
        {
        public:
            friend class List;
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type = T;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

            

            reference operator*() const;
            pointer operator->();

            List_Iterator& operator++();
            List_Iterator operator++(int);
    
            List_Iterator& operator--();
            List_Iterator operator--(int);

            bool operator==(List_Iterator const& rhs) const;
            bool operator!=(List_Iterator const& rhs) const;

        private:  
            List_Iterator(Node* ptr); 
            Node* m_ptr;
        }; 
    public:
        List_Iterator begin();
        List_Iterator end();
    };
}

#include "List.tcc"
#endif //LIST_H
