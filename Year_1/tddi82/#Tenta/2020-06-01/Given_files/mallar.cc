#include <iostream>
#include <vector>

class Sum_Handler
{
public:

    using value_type = int;
    
    Sum_Handler(int start = {})
        : start{start}
    { }
    
    int initial() const
    {
        return start;
    }

    int combine(int result, int value) const
    {
        return result + value;
    }
    
private:
    int start {};    
};

struct Accumulator
{
public:

    Accumulator(std::vector<int>::iterator begin, std::vector<int>::iterator end, Sum_Handler handler = {})
        : data{begin, end}, handler{handler}
    { }

    void push(int value)
    {
        data.push_back(value);
    }

    void pop()
    {
        data.pop_back();
    }
    
    int evaluate() const
    {
        int result {handler.initial()};
        for (int value : data)
        {
            result = handler.combine(result, value);
        }
        return result;
    }
    
private:
    
    Sum_Handler handler {};
    std::vector<int> data {};
    
};

int main()
{
    std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Accumulator a1 { v.begin(), v.end() };

    // prints: 55
    std::cout << a1.evaluate() << std::endl;

    Sum_Handler h2 {10};
    Accumulator a2 { v.begin(), v.end(), h2 };
    a2.pop();
    a2.push(11);

    // prints: 66
    std::cout << a2.evaluate() << std::endl;
}
