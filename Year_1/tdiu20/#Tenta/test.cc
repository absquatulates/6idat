#include <stdexcept> 
#include <iostream>

class Interval
{
public:

Interval(int i)
    : value{i}
{
    valid(i);
}

int get() const
{
    return value;
}

private:

    int value;

    void valid(int i) const
    {
        if (i<15 || i >35)
        {
            throw std::logic_error{"Out of range [15,35]"};
        }
    }

};

int main()
{
    Interval i{20};

    std::cout << i.get() << std::endl;
    
}