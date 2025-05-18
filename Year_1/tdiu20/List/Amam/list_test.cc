#include "catch.hpp"
#include "List.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

TEST_CASE("Empty")
{
    List l0{};
    List l1{1};

    CHECK( l0.empty() );
    CHECK_FALSE( l1.empty() );

}

TEST_CASE("Size & Insert")
{
    List l0{};
    List l1{1};
    List l2{2, 1};
    List l3{1, 4, 6, 7, 8};

    SECTION("Size")
    {
        CHECK( l0.size() == 0 );
        CHECK( l1.size() == 1 );
        CHECK( l2.size() == 2 );
        CHECK( l3.size() == 5 );  
    }

    SECTION("Insert")
    {
        l0.insert(2);
        l1.insert(4);
        l1.insert(9);

        CHECK( l0.size() == 1 );
        CHECK( l1.size() == 3 );
    }
}

TEST_CASE("to_string")
{
    List l0{1, 2, 3, 4};
    List l1{4, 3, 2, 1};
    List l2{3, 1, 4, 2};

    CHECK( l0.to_string() == "1 2 3 4" );
    CHECK( l1.to_string() == "1 2 3 4" );
    CHECK( l2.to_string() == "1 2 3 4" );
}

TEST_CASE("Clear & Remove")
{
    List l0{1, 3, 5, 6, 7};
    List l1{5, 7, 3, 8};

    SECTION("Remove")
    {
        CHECK_THROWS( l0.remove(-6) );
        CHECK_THROWS( l1.remove(102) );

        l0.remove(3);
        l1.remove(2);

        CHECK( l0.size() == 4 );
        CHECK( l0.to_string() == "1 3 5 7" );
        CHECK( l1.size() == 3 );
        CHECK( l1.to_string() == "3 5 8" );
    }

    SECTION("Clear")
    {
        l0.clear();
        l1.clear();

        CHECK( l0.empty() );
        CHECK( l1.empty() );
    }
}

TEST_CASE("at")
{
    List l0{1, 3, 5, 6, 7};
    List l1{5, 7, 3, 8};

    CHECK_THROWS(l0.at(-2));
    CHECK_THROWS(l1.at(13));

    CHECK( l0.at(0) == 1);
    CHECK( l0.at(1) == 3);
    CHECK( l0.at(2) == 5);
    CHECK( l0.at(3) == 6);
    CHECK( l0.at(4) == 7);

    CHECK( l1.at(0) == 3);
    CHECK( l1.at(1) == 5);
    CHECK( l1.at(2) == 7);
    CHECK( l1.at(3) == 8);
}


TEST_CASE("Copy & =")
{
    List l0{3, 5, 2, 1, 6};

    SECTION("Copy")
    {
        List l1{l0.copy()};
        CHECK( l0.to_string() == l1.to_string() );
    }

    SECTION("=")
    {
        List l2{};
        List l3{};

        l2 = l0;
        CHECK( l0.to_string() == l2.to_string() );

        l0 = std::move(l3);
        CHECK( l0.to_string() != l3.to_string() );
        CHECK( l0.empty() );
        CHECK( l3.to_string() == "1 2 3 5 6" );
    }
}

TEST_CASE("<<")
{
    stringstream ss;
    List l0{};
    List l1{1, 2, 3, 4};

    SECTION("l0")
   {
      ss << l0;
      CHECK( ss.str() == "" );
      CHECK( ss.str() == l0.to_string() );   
   }

   SECTION("l1")
   {
      ss << l1;
      CHECK( ss.str() == "1 2 3 4" );
      CHECK( ss.str() == l1.to_string() );
   }
}

TEST_CASE("Bonus")
{
    List l0{9, 8, 7, 6, 5, 4, 3, 1, 2};

    CHECK_THROWS( l0.sub({1, 3, 2}) );
    CHECK_THROWS( l0.sub({200}));
    CHECK_THROWS( l0.sub({-1}));

    CHECK( (l0.sub({0})).to_string() == "1" );
    CHECK( (l0.sub({4, 5})).to_string() == "5 6" );
    CHECK( (l0.sub({0, 1, 1, 1})).to_string() == "1 2 2 2" );
}
