#include <numeric>
#include <functional>
#include <cmath>
#include <vector>
#include <iostream>
#include <iterator>
#include <random>
#include <algorithm>
using namespace std;

bool is_prime(int n)
{
    if ( n < 2 || ( n > 2 && n % 2 == 0 ) )
        return false;
    for ( int i {3}; i < sqrt(n); i+=2 )
    {
        if ( n % i == 0 )
            return false;
    }
    return true;
}

int main()
{
    random_device rnd;
    uniform_int_distribution<int> dist{2,75};
    vector<int> factors(10);
    generate(begin(factors), end(factors), [&]{ return dist(rnd); });
    auto it = remove_if(begin(factors), end(factors), [](int i){return !is_prime(i); });
    factors.erase(it, end(factors));
    sort(begin(factors), end(factors));
    auto number { accumulate(begin(factors), end(factors),1, multiplies<>{}) };
    cout << "Random number: " << number << '\n'
         << "factors: ";
    copy(begin(factors), end(factors), ostream_iterator<int>{cout, " "});
    cout << endl;
}
