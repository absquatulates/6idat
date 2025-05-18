#include "catch.hpp"
#include "List.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

TEST_CASE("Insert & Size")
{

    List l0{};
    List l1{2, 7, 5, 1, 9, 0};
    List l2{3, 5, 2, 7};

    CHECK( l0.size() == 0 );
    CHECK( l1.size() == 6 );

    //l1.insert(8);

    CHECK( l1.size() == 6 );

    CHECK( l0.empty() );
    CHECK_FALSE( l1.empty() );

    CHECK( l1.at(0) == 0 );
    CHECK( l1.at(1) == 1 );
    CHECK( l1.at(2) == 2 );
    CHECK( l1.at(3) == 5 );

    l1.remove(2);
    CHECK( l1.size() == 5);
    CHECK( l1.at(2) == 5 );
    CHECK( l1.at(1) == 1 );

    CHECK( l0.to_string() == "" );
    CHECK( l1.to_string() == "01579" );
    CHECK( l2.to_string() == "2357" );

    l1.clear();
    CHECK( l1.to_string() == "" );

}