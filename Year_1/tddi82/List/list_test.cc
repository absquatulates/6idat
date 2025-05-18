
#include "List.h"
#include "catch.hpp"

TEST_CASE( "Create list" )
{
    List lst{1,4,2,6,8,9};
    CHECK(lst.at(0) == 1);
    CHECK(lst.at(2) == 2);
    CHECK_THROWS(lst.at(6));
    CHECK(lst.at(-1) == lst.at(0));
    CHECK(lst.at(-30) == lst.at(0));

    CHECK(lst.size() == 6);


    List l2;
    l2 = lst;

    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
    CHECK(l2.at(3) == lst.at(3));
    CHECK_FALSE(l2.empty());

    CHECK(l2.at(3)  == 6);
    l2.at(3) = 3;
    CHECK(l2.at(3) == 3);

    
}

