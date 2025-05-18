#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main()
{
    // 1.
    int m {};
    std::cin >> m;

    // 2.
    std::vector<int> v {};

    // 3. & 4.

    auto operation = [](int x)
                     {
                         return /* beräkna din tilldelade formel */;
                     };
    
    std::transform(std::istream_iterator<int>{std::cin},
                   std::istream_iterator<int>{},
                   std::back_inserter(v), operation);

    // 5.
    auto order = [&m](int x, int y)
                 {
                     return /* gör din tilldelade jämförelse */;
                 };
    std::sort(v.begin(), v.end(), order);

    // 6.

    // Här fanns det lite olika varianter:

    // Variant 1:
    // auto it = std::remove_if(v.begin(), v.end(), [](int x) { return x <= 0; });
    // v.erase(it, v.end());

    // Variant 2:
    // auto it = std::max_element(v.begin(), v.end());
    // v.erase(it);

    // Variant 3:
    // auto it = std::find_if(v.begin(), v.end(), [](int x) { return x % 3 == 0; });
    // v.erase(it);

    // 7.
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout, " "});

    // 8.

    // Här fanns det två varianter:

    // Variant 1:
    // std::cout << std::accumulate(std::begin(v), std::end(v), 0) << std::endl;

    // Variant 2:
    // std::cout << std::count_if(std::begin(v), std::end(v), [](int x) { return x % 2 == 0; }) << std::endl;
}
