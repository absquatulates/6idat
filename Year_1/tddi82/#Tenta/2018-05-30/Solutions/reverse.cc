#include <vector>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
using namespace std;

template <typename Container>
Container reverse(Container const & orig)
{
    Container c { orig };
    std::reverse(begin(c), end(c));
    return c;
}

#include "catch.hpp"
TEST_CASE("vector<int>")
{
    vector<int> values   {1,2,3,4,5};
    vector<int> reversed {5,4,3,2,1};
    auto res { reverse(values) };
    CHECK(std::equal(begin(reversed), end(reversed), begin(res)));
}
TEST_CASE("list<char>")
{
    list<char> values   {'a','b','c','d'};
    list<char> reversed {'d','c','b','a'};
    auto res { reverse(values) };
    CHECK(std::equal(begin(reversed), end(reversed), begin(res)));
}
TEST_CASE("string")
{
    string values   {"abcdef"};
    string reversed {"fedcba"};
    auto res { reverse(values) };
    CHECK(std::equal(begin(reversed), end(reversed), begin(res)));
}

