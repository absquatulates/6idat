#include <stdexcept>
#include <sstream>
#include <vector>
#include <iostream>

// Operator som tillÃ¥ter oss att testa Map_Filter och
// Remove_And_Increase med std::string. MÃ¥ste inte anvÃ¤ndas men kan
// underlÃ¤tta vid testning av olika datatyper.
std::string operator+(std::string const& s, int i) 
{
  return s + std::to_string(i);
}


class Remove_And_Increase
{
public:

    Remove_And_Increase(int target)
        : target{target}
    { }

    bool valid(int value) const
    {
        return value != target;
    }

    int transform(int value) const
    {
        return value + 1;
    }

private:

    int target;
    
};

class Map_Filter
{
    using value_type = std::vector<int>::value_type;
    using iterator   = std::vector<int>::iterator;
public:

    Map_Filter(std::vector<int>& container, Remove_And_Increase policy)
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
    Remove_And_Increase policy;
};

int main()
{
    std::vector<int> v { 1, 5, -2, 67, 1, 23, 15, -76, 1 };
    {
        Map_Filter mf { v, Remove_And_Increase{1} };
        while (!mf.done())
        {
            std::cout << mf.next() << " ";
        }
        std::cout << std::endl;
    }

    {
        Map_Filter mf { v, Remove_And_Increase{0} };
        while (!mf.done())
        {
            std::cout << mf.next() << " ";
        }
        std::cout << std::endl;
    }
}
