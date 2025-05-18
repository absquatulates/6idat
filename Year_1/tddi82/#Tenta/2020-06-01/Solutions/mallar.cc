#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
class Sum_Handler
{
public:

    using value_type = T;
    
    Sum_Handler(T start = {})
        : start{start}
    { }
    
    T initial() const
    {
        return start;
    }

    T combine(T const& result, T const& value) const
    {
        return result + value;
    }
    
private:
    T start {};    
};

// VG-del
template <typename T>
class String_Handler
{
public:

    using value_type = std::string;

    std::string initial() const
    {
        return "";
    }

    std::string combine(std::string const& result, T const& value) const
    {
        std::ostringstream oss {};
        oss << result << value << ' ';
        return oss.str();
    }
};

// Handler parametern behövs endast för VG-delen

// Notera att Accumulator INTE ska ta en behållare utan den ska ta en
// godtycklig datatyp T
template <typename T, typename Handler = Sum_Handler<T>>
struct Accumulator
{
public:

    // Om vi gör konstruktorn till en template så kan vi ta emot
    // vilken iterator vi vill, oberoende av vad T är.
    template <typename It>
    Accumulator(It begin, It end, Handler handler = {})
        : data{begin, end}, handler{handler}
    { }

    void push(T value)
    {
        data.push_back(value);
    }

    void pop()
    {
        data.pop_back();
    }
    
    typename Handler::value_type evaluate() const
    {
        typename Handler::value_type result {handler.initial()};
        for (T value : data)
        {
            result = handler.combine(result, value);
        }
        return result;
    }
    
private:
    
    Handler handler {};
    std::vector<T> data {};
    
};

int main()
{
    std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Accumulator<int> a1 { v.begin(), v.end() };

    // prints: 55
    std::cout << a1.evaluate() << std::endl;

    Sum_Handler<double> h2 {10.0};
    Accumulator<double> a2 { v.begin(), v.end(), h2 };
    a2.pop();
    a2.push(11.66);

    // prints: 66.66
    std::cout << a2.evaluate() << std::endl;

    String_Handler<int> h3 {};
    Accumulator<int, String_Handler<int>> a3 { v.begin(), v.end() };

    // prints: 1 2 3 4 5 6 7 8 9 10
    std::cout << a3.evaluate() << std::endl;
}
