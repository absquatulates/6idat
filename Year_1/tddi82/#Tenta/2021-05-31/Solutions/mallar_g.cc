#include <stdexcept>
#include <sstream>
#include <vector>
#include <iostream>

template <typename T>
class Remove_And_Increase
{
public:

    Remove_And_Increase(T const& target)
        : target{target}
    { }

    bool valid(T const& value) const
    {
        return value != target;
    }

    T transform(T const& value) const
    {
        return value + 1;
    }

private:

    T target;
    
};

template <typename Container>
class Map_Filter
{
    using value_type = typename Container::value_type;
    using iterator   = typename Container::iterator;
public:

    Map_Filter(Container& container, Remove_And_Increase<value_type> policy)
        : begin{container.begin()}, end{container.end()}, policy{policy}
    {
        to_next();
    }

    value_type next()
    {
        if (done())
        {
            throw std::out_of_range{"Reached the end"};            
        }
        
        iterator save { begin };

        ++begin;
        to_next();
        
        return policy.transform(*save);
    }

    bool done() const
    {
        return begin == end;
    }

private:

    void to_next()
    {
        while (begin != end && !policy.valid(*begin))
        {
            ++begin;
        }
    }
    
    iterator begin;
    iterator end;
    Remove_And_Increase<value_type> policy;
};

int main()
{
    std::vector<int> v { 1, 5, -2, 67, 1, 23, 15, -76, 1 };
    {
        Map_Filter<std::vector<int>> mf { v, Remove_And_Increase<int>{1} };
        while (!mf.done())
        {
            std::cout << mf.next() << " ";
        }
        std::cout << std::endl;
    }

    {
        Map_Filter<std::vector<int>> mf { v, Remove_And_Increase<int>{0} };
        while (!mf.done())
        {
            std::cout << mf.next() << " ";
        }
        std::cout << std::endl;
    }
}
