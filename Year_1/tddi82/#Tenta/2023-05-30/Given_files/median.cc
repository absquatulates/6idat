#include <iostream>
#include <cmath> // fÃ¶r std::abs
#include <vector>
#include <array>
#include <string>

/* Implementera median() hÃ¤r */

bool compare_abs(int a, int b)
{
    return std::abs(a) < std::abs(b);
}

struct Compare
{
public:

    Compare(char target)
        : target { target }
    { }

    bool operator()(std::string a, std::string b)
    {
        return count(a) < count(b);
    }

    int count(std::string str)
    {
        int result { 0 };
        for (char c : str)
        {
            if (c == target)
            {
                ++result;
            }
        }
        return result;
    }
    
private:
    char target;
};

int main()
{
    std::vector<int> v { 1, 7, -3, 2, -1, 8 };
    std::cout << median(v, [](int a, int b) { return a < b; }) << std::endl;
    std::cout << median(v, [](int a, int b) { return a > b; }) << std::endl;

    // Sortera *som om* negativa tal var positiva
    std::cout << median(v, compare_abs) << std::endl;

    Compare comp { 'a' };
    std::array<std::string, 6> l
    {
        "ananasar",
        "ananas",
        "ananasarna",
        "apelsin",
        "apelsinerna",
        "kiwi"
    };
    std::cout << median(l, comp) << std::endl;
}
