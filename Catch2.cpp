#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "SmallLibrary8.0.cpp"

// TEST_CASE("library System", "[LibrarySystem]")
// { Person person("Cozy", "Gotham", "Cozy@hotmail.com");


//     REQUIRE(person.getName()=="Cozy");
//     REQUIRE(person.getAddress()=="Gotham");
//     REQUIRE(person.getEmail()=="Cozy@hotmail.com");


// }

TEST_CASE("Library System", "[LibrarySystem]")
{Member member(1, "Cozy", "Cozy@hotmail.com", "GothamCity");

    REQUIRE(member.getMemberID()==1);


};

TEST_CASE("Library System2", "[LibrarySystem]")
{Book book(1, "CozyBook", "Cozy", "King");

    REQUIRE(book.getBookID()==1);


};