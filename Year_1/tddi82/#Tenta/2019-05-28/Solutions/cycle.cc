#include <stdexcept>
#include <vector>
#include <deque>
#include <string>

using namespace std;

template <typename Container>
class Cycle
{
public:

  using value_type = typename Container::value_type;
  
  Cycle(Container& container) : container{container}
  { }

  size_t size() const
  {
    return container.size();
  }

  value_type const& at(int index) const
  {
    if (index < 0)
      throw out_of_range{"negative index"};
    return container.at(index % size());
  }

  value_type& at(int index)
  {
    if (index < 0)
      throw out_of_range{"negative index"};
    return container.at(index % size());
  }
  
private:

  Container& container;
  
};

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("int vector") {
  vector<int> v {1, 2, 3, 4};
  Cycle<vector<int>> c {v};
  for (int i{0}; i < c.size(); ++i)
  {
    CHECK (c.at(i) == v.at(i));
    CHECK (c.at(i + v.size()) == v.at(i));
    CHECK (c.at(i + 2 * v.size()) == v.at(i));
  }

  c.at(0) = 5;
  CHECK(v.at(0) == 5);

  CHECK_THROWS(v.at(-1));
}

TEST_CASE("string deque") {
  deque<string> d {"programmering", "kul", "C++"};
  Cycle<deque<string>> const c {d};
  for (int i{0}; i < c.size(); ++i)
  {
    CHECK (c.at(i) == d.at(i));
    CHECK (c.at(i + d.size()) == d.at(i));
    CHECK (c.at(i + 2 * d.size()) == d.at(i));
  }
}
