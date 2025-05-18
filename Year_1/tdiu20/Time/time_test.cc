// Komplettering: Era tester måste gå igenom! Jag missade att anmärka 
// på det vid förra inlämningen, så därför har ni fortfarande möjlighet
// att få bonusen för endast en komplettering

#include "catch.hpp"
#include "Time.h"
#include <iostream>
#include <sstream>

using namespace std;

TEST_CASE ("Constructors and getters")
{

   SECTION("Default")
   {    
      Time empty{};
      CHECK( empty.get_hour()   == 0 );
      CHECK( empty.get_minute() == 0 );
      CHECK( empty.get_second() == 0 );
   }

   SECTION("Integer")
   {
      Time t0{0,0,0};
      Time t1{12,30,30};
      Time t2{23,59,59};

      CHECK_THROWS( Time{13,35,60} );
      CHECK_THROWS( Time{13,60,35} );
      CHECK_THROWS( Time{24,35,35} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
   }

   SECTION("24h String")
   {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};

      CHECK_THROWS( Time{"13:35:60"} );
      CHECK_THROWS( Time{"13:60:35"} );
      CHECK_THROWS( Time{"24:35:35"} );

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );  
   }

   SECTION("12h String")
   {
      Time t0{"12:00:00am"};
      Time t1{"12:30:30pm"};
      Time t2{"11:59:59pm"};

      CHECK_THROWS( Time{"01:35:60pm"} );
      CHECK_THROWS( Time{"01:60:35pm"} );
      CHECK_THROWS( Time{"13:35:35am"} );
      CHECK_THROWS( Time{"20:15:52pm"} );

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );  
   }

}
TEST_CASE ("is_am") 
{
   Time t0{"05:00:00"};
   Time t1{"14:00:00"};
   Time t2{"11:12:00pm"};
   Time t3{0, 0, 0};
   Time t4{12, 0, 0};
   Time t5{"12:00:00pm"};
   Time t6{"12:00:00am"};

   CHECK( t0.is_am() );
   CHECK_FALSE( t1.is_am() );
   CHECK_FALSE( t2.is_am() );
   CHECK( t3.is_am() );
   CHECK_FALSE( t4.is_am() );
   CHECK_FALSE( t5.is_am() );
   CHECK( t6.is_am() );
}

TEST_CASE ("to_string")
{
   Time t0{};
   Time t1{13, 0, 0};
   Time t2{23, 59, 59};
   Time t3{"12:01:01am"};
   Time t4{"01:34:23pm"};
   Time t5{"05:13:18pm"};
   Time t6{"05:13:18am"};


   SECTION("to 24 hour format")
   {
      CHECK( t0.to_string() == "00:00:00" );
      CHECK( t1.to_string() == "13:00:00" );
      CHECK( t2.to_string() == "23:59:59" );
   }

   SECTION("12 hour format to 24 hour format")
   {
      CHECK( t3.to_string() == "00:01:01" );
      CHECK( t4.to_string() == "13:34:23" );
      CHECK( t5.to_string() == "17:13:18" );
      CHECK( t6.to_string() == "05:13:18" );
   }

   SECTION("to 24 hour format with argument")
   {
      CHECK( t0.to_string(false) == "00:00:00" );
      CHECK( t1.to_string(false) == "13:00:00" );
      CHECK( t2.to_string(false) == "23:59:59" );
      CHECK( t3.to_string(false) == "00:01:01" );
      CHECK( t4.to_string(false) == "13:34:23" );
      CHECK( t5.to_string(false) == "17:13:18" );
      CHECK( t6.to_string(false) == "05:13:18" );
   }

   SECTION("to 12 hour format")
   {
      CHECK( t0.to_string(true) == "12:00:00am" );
      CHECK( t1.to_string(true) == "01:00:00pm" );
      CHECK( t2.to_string(true) == "11:59:59pm" );
      CHECK( t3.to_string(true) == "12:01:01am" );
      CHECK( t4.to_string(true) == "01:34:23pm" );
      CHECK( t5.to_string(true) == "05:13:18pm" );
      CHECK( t6.to_string(true) == "05:13:18am" );
   }
}


TEST_CASE ("++ & --")
{
   Time t0{0, 0, 0};
   Time t1{0, 0, 1};
   Time t2{12, 10, 1};
   Time t3{12, 10, 0};
   Time t4{"00:00:00"};
   Time t5{"00:00:01"};
   Time t6{"13:15:51"};
   Time t7{"13:15:50"};
   Time t8{23, 59, 59};
   Time t9{};
   
   SECTION("++")
   {
      t0++;
      ++t4;
      CHECK( t0 == t1 );
      CHECK( t4 == t5 );
      CHECK( t4++ != ++t0 );
      CHECK( ++t5 != t1++ );
      t8++; 
      CHECK( t8 == t9 );
   }

   SECTION("--")
   {
      t2--;
      --t6;
      CHECK( t2 == t3 );
      CHECK( t6 == t7 );
      CHECK( t2-- != --t6 );
      CHECK( --t3 != t7-- );
      t0--;
      CHECK( t0 == t8 );
   }

   
}

TEST_CASE ("<>!=")
{
   Time t0{14, 15, 6};
   Time t1{13, 5, 2};
   Time t2{14, 10, 55};
   Time t3{14, 15, 5};
   Time t4{14, 15, 6};
   Time t5{13, 5, 2};

   SECTION(">")
   {
      CHECK( t0 > t1 );
      CHECK_FALSE( t1 > t0 );
      CHECK_FALSE( t0 == t1 );
   }

   SECTION("<")
   {
      CHECK( t2 < t0 );
      CHECK_FALSE( t0 < t2 );
      CHECK_FALSE( t0 == t2 );
   }

   SECTION(">=")
   {
      CHECK( t0 >= t2 );
      CHECK( t0 >= t4 );
      CHECK_FALSE( t2 >= t4 );
   }

   SECTION("<=")
   {
      CHECK( t2 <= t0 );
      CHECK( t0 <= t4 );
      CHECK_FALSE( t4 <= t2 );
   }

   SECTION("!=")
   {
      CHECK( t1 != t0 );
      CHECK( t2 != t0 );
      CHECK_FALSE( t0 != t4 );
   }

   SECTION("==")
   {
      CHECK( t0 == t4 );
      CHECK( t1 == t5 );
      CHECK_FALSE( t1 == t3 );
      CHECK_FALSE( t0 == t2 );
   }


}

TEST_CASE("Bonus")
{   
   Time t0{14, 15, 6};

   Time t1{14, 15, 7};
   Time t2{14, 16, 6};
   Time t3{15, 15, 6};

   Time t4{14, 20, 48};
   Time t5{14, 36, 1};
   Time t6{17, 40, 51};
   Time t7{18, 1, 46};
   
   Time t8{14, 15, 5};
   Time t9{14, 14, 6};
   Time t10{13, 15, 6};

   Time t11{14, 9, 24};
   Time t12{13, 54, 11};
   Time t13{10, 49, 21};
   Time t14{10, 28, 26};


   SECTION("+")
   {
      SECTION("Time + int")
      {
        CHECK( t0 + 1 == t1 );
        CHECK( (t0 + 1).to_string() == "14:15:07" );
        CHECK( t0 + 60 == t2);
        CHECK( (t0 + 60).to_string() == "14:16:06" );
        CHECK( t0 + 3600 == t3 );
        CHECK( (t0 + 3600).to_string() == "15:15:06" );
        CHECK( t0 + 86401 == t1 );
        CHECK( (t0 + 86401).to_string() == "14:15:07" );

        CHECK( t0 + (-1) == t8 ); 
        CHECK( t0 + (-60) == t9 ); 
        CHECK( t0 + (-3600) == t10 ); 
        CHECK( t0 + (-86401) == t8 ); 

        CHECK( t0 + 342 == t4 );
        CHECK( t0 + 1255 == t5 );
        CHECK ( t0 + 12345 == t6 );
        CHECK( t0 + 100000 == t7 );
      }

      SECTION("int + Time")
      {
        CHECK( 1 + t0 == t1 );
        CHECK( 60 + t0 == t2);
        CHECK(3600 + t0 == t3 );
        CHECK(86401 + t0 == t1 );

        CHECK( (-1) + t0 == t8 ); 
        CHECK( (-60) + t0 == t9 ); 
        CHECK( (-3600) + t0 == t10 ); 
        CHECK( (-86401) + t0 == t8 ); 

        CHECK( 342 + t0 == t4 );
        CHECK( 1255 + t0 == t5 );
        CHECK ( 12345 + t0 == t6 );
        CHECK( 100000 + t0 == t7 );
      }
   }

   SECTION("-")
   {
        CHECK( t0 - 1 == t8 );
        CHECK( (t0 - 1).to_string() == "14:15:05" );
        CHECK( t0 - 60 == t9 );
        CHECK( (t0 - 60).to_string() == "14:14:06" );
        CHECK( t0 - 3600 == t10 );
        CHECK( (t0 - 3600).to_string() == "13:15:06" );
        CHECK( t0 - 86401 == t8 );
        CHECK( (t0 - 86401).to_string() == "14:15:05" );

        CHECK( t0 - (-1) == t1 );
        CHECK( t0 - (-60) == t2);
        CHECK( t0 - (-3600) == t3 );
        CHECK( t0 - (-86401) == t1 );

        CHECK( t0 - 342 == t11 );
        CHECK( t0 - 1255 == t12 );
        CHECK ( t0 - 12345 == t13 );
        CHECK( t0 - 100000 == t14 );  
   }

   SECTION("+=")
   {
      CHECK( (t0 += 1) == t0 + 1 );
      CHECK( (t0 += 1) == (t0 = t0 + 1));
      CHECK( (t0 += 373) == t0 + 373 );
      CHECK( (t0 += 373) == (t0 = t0 + 373));
      CHECK( (t0 += 9477) == t0 + 9477 );
      CHECK( (t0 += 9477) == (t0 = t0 + 9477));
      CHECK( (t0 += 98765) == t0 + 98765 );
      CHECK( (t0 += 98765) == (t0 = t0 + 98765));
   }
   
   
   SECTION("-=")
   {
      CHECK( (t0 -= 1) == t0 - 1 );
      CHECK( (t0 -= 1) == (t0 = t0 - 1) );
      CHECK( (t0 -= 373) == t0 - 373 );
      CHECK( (t0 -= 373) == (t0 = t0 - 373) );
      CHECK( (t0 -= 9477) == t0 - 9477 );
      CHECK( (t0 -= 9477) == (t0 = t0 - 9477) );
      CHECK( (t0 -= 98765) == t0 - 98765 );
      CHECK( (t0 -= 98765) == (t0 = t0 - 98765) );
   }
}


TEST_CASE("Skriva till ström")
{
   stringstream ss;
   Time t0{12, 1, 2};
   Time t1{};

   SECTION("Ut_1")
   {
      ss << t0;
      CHECK( ss.str() == "12:01:02" );   
   }

   SECTION("Ut_2")
   {
      ss << t1;
      CHECK( ss.str() == "00:00:00" );
   }
}

TEST_CASE("Läsa från ström")
{
   stringstream ss;
   Time t0{12, 1, 2};
   Time t1{}; 
   SECTION("In")
   {
      ss << t0;
      ss >> t1;
      CHECK( ss.str() == "12:01:02" );
      CHECK( t1 == t0);
   }
}


// Fill with more tests of other functions and operators!

