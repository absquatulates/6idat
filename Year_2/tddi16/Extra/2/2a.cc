#include <iostream>
#include <vector>

int digitSum(int n) 
{
    return (n % 9 == 0) ? 9 : n % 9;
}

int main() {
    int n;
    std::vector<int> sum{};

    
    while (std::cin >> n && n != 0) 
    {
        sum.push_back(digitSum(n));
    }

    for (int i : sum)
        std::cout << i << std::endl;

}