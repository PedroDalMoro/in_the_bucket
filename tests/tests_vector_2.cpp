#include "catch2/catch_amalgamated.hpp"
#include "vector_2.hpp"

TEST_CASE("Testing set vector values")
{
    Vec2 sut(0, 0); 

    sut.set(5, 5);
    REQUIRE(sut.x == 5.0f);
    REQUIRE(sut.y == 5.0f);     // add erro
}

// TEST_CASE("Another test case")
// {
//     REQUIRE(1 == 1);
// }