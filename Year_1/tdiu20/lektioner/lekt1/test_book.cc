#include "catch.hpp"
#define CATCH_CONFIG_MAIN
#include "lekt1.h"

using namespace std;

Test_case("Init")
{
    Book Book1{"Pippi Långstrump", "Barn", "Astrid Lindgren", 301, "I Lager", 1945};
    Book Book2{"Pippi Långstrump", "Barn", "Astrid Lindgren", 301, "I Lager", 1945};

    check(book1.get_year() == 1945);
    check(book1.get_genre() == "Barn");
    check(book1 > book2);

}