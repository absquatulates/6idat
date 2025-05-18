
#include "List.h"
#include "catch.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace List_NS;

TEST_CASE( "Create list" )
{
    List lst{1,4,2,6,8,9};
    CHECK(lst.at(0) == 1);
    CHECK(lst.at(2) == 2);
    CHECK_THROWS(lst.at(6));
    CHECK(lst.at(-1) == lst.at(0));
    CHECK(lst.at(-30) == lst.at(0));

    CHECK(lst.size() == 6);


    List<int> l2;
    l2 = lst;

    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
    CHECK(l2.at(3) == lst.at(3));
    CHECK_FALSE(l2.empty());

    CHECK(l2.at(3)  == 6);
    l2.at(3) = 3;
    CHECK(l2.at(3) == 3);

    List l3{'a','d','c'};

    CHECK(l3.at(0) == 'a');

    List<std::string> l4{"hugo", "adam", "oskar", "denis", "vilgot", "a" };
    CHECK(l4.at(0) == "hugo");


    List l5{5.2, 3.0, 6.12};

    List l6{lst, l2};

    List l7{l2, lst};
    List l8{l6, l7};

    CHECK(l6.at(0).at(0) == l6.at(1).at(0));

    CHECK(l8.at(0).at(0).at(0) == l8.at(1).at(0).at(0));
    CHECK(l8.at(0).at(1).size() == l8.at(1).at(0).size()); 

}

TEST_CASE("Int")
{
    List<int> l0{};
    List<int> l1{0};
    List<int> l2{1, 2, 3, 4, 5};
    List<int> l3{4, 3, 5, 1, 0, 2};

    SECTION("Size")
    {
        CHECK(l0.empty());
        CHECK_FALSE(l1.empty());

        CHECK(l0.size() == 0);
        CHECK(l1.size() == 1);
        CHECK(l2.size() == 5);
        CHECK(l3.size() == 6);
    }

    SECTION("Front/Back")
    {
        CHECK(l2.front() == 1);
        CHECK(l3.front() == 4);
        CHECK(l2.back() == 5);
        CHECK(l3.back() == 2);

        l2.push_front(9);
        l3.push_front(7);
        CHECK(l2.front() == 9);
        CHECK(l3.front() == 7);

        l2.push_back(-1);
        l3.push_back(-3);
        CHECK(l2.back() == -1);
        CHECK(l3.back() == -3);
    }

    SECTION("at")
    {
        CHECK(l1.at(0) == 0);
        CHECK(l2.at(2) == 3);
        CHECK(l3.at(5) == 2);

        CHECK_THROWS(l0.at(0));
        CHECK_THROWS(l1.at(1));
    }

    SECTION("Swap")
    {
        CHECK(l2.at(0) == 1);
        CHECK(l3.at(0) == 4);

        l2.swap(l3);

        CHECK_FALSE(l2.at(0) == 1);
        CHECK_FALSE(l3.at(0) == 4);
        CHECK(l2.at(0) == 4);
        CHECK(l3.at(0) == 1);
        
    }
}

TEST_CASE("Double")
{
    List<double> l0{};
    List<double> l1{0.0};
    List<double> l2{1.2, 2.3, 3.4, 4.5, 5.6};
    List<double> l3{4.98, 3.87, 5.76, 1.65, 0.54, 2.43};

    SECTION("Size")
    {
        CHECK(l0.empty());
        CHECK_FALSE(l1.empty());

        CHECK(l0.size() == 0);
        CHECK(l1.size() == 1);
        CHECK(l2.size() == 5);
        CHECK(l3.size() == 6);
    }

    SECTION("Front/Back")
    {
        CHECK(l2.front() == 1.2);
        CHECK(l3.front() == 4.98);
        CHECK(l2.back() == 5.6);
        CHECK(l3.back() == 2.43);

        l2.push_front(9.2);
        l3.push_front(7.74);
        CHECK(l2.front() == 9.2);
        CHECK(l3.front() == 7.74);

        l2.push_back(-1.5);
        l3.push_back(-3.21);
        CHECK(l2.back() == -1.5);
        CHECK(l3.back() == -3.21);
    }

    SECTION("at")
    {
        CHECK(l1.at(0) == 0);
        CHECK(l2.at(2) == 3.4);
        CHECK(l3.at(5) == 2.43);

        CHECK_THROWS(l0.at(0));
        CHECK_THROWS(l1.at(1));

        l1.at(0) = 2;
        CHECK(l1.at(0) == 2);
    }

    SECTION("Swap")
    {
        CHECK(l2.at(0) == 1.2);
        CHECK(l3.at(0) == 4.98);

        l2.swap(l3);

        CHECK_FALSE(l2.at(0) == 1.2);
        CHECK_FALSE(l3.at(0) == 4.98);
        CHECK(l2.at(0) == 4.98);
        CHECK(l3.at(0) == 1.2);
        
    }
}

TEST_CASE("Init")
{

    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{3, 2, 1};

    List<int> int_list{1, 2, 3, 4};
    List<int> int_list2{4, 3, 1, 2};
    List<double> double_list{2.2, 3.42, 2.533};
    List<char> char_list{'W', 'I', 'L', 'L', 'I', 'A', 'M'};
    List<std::string> str_list{"Malte", "är", "en", "legend!"};
    List<bool> bool_list{true, false, true, true, false, false, false, true};
    List list_list{int_list, int_list2};
    List<std::vector<int>> vector_list{v1, v2};
}

TEST_CASE("Iterator")
{
    SECTION("++/--")
    {
        List<int> l0{1, 2, 3, 4};
        List<int> l1{1, 2};

        CHECK(l0.begin() != l0.end());
        CHECK(l0.begin()++ != l0.end()--);
        CHECK(++l1.begin() == --l1.end());

        auto rb{std::make_move_iterator(l0.begin())};
        auto rb2{l0.begin()};
        auto rb3{l0.begin()};

        rb++;
        ++rb3;
        CHECK(*rb == 2);
        CHECK(*rb2 == 1);
        CHECK(*rb3 == 2);

        auto re{std::make_move_iterator(l0.end())};
        auto re2{l0.end()};

        re--;
        --re2;
        --re2;
        CHECK(*re == 4);
        CHECK(*re2 == 3);
    }
   

    SECTION("->")
    {
        List<std::string> Malte{"MALTE", "MALTE", "MALTE"};

        auto rmalte{Malte.begin()};
        CHECK(rmalte->size() == 5);
    }


}