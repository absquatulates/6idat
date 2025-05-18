#include <vector>
#include <deque>
#include <string>

using namespace std;

// plats fÃ¶r cycle

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("int vector") {
  vector<int> v {1, 2, 3, 4};
  Cycle<vector<int>> c {v};
  for (int i{0}; i < v.size(); ++i)
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
  for (int i{0}; i < d.size(); ++i)
  {
    CHECK (c.at(i) == d.at(i));
    CHECK (c.at(i + d.size()) == d.at(i));
    CHECK (c.at(i + 2 * d.size()) == d.at(i));
  }
}
