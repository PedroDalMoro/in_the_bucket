#include "catch2/catch_amalgamated.hpp"
#include "vector_2.hpp"

TEST_CASE("Testing set vector values")
{
    Vec2 sut(0, 0); 

    sut.set(5, 5);
    REQUIRE(sut.x == 7.0f);
    REQUIRE(sut.y == 5.0f);
}

// Acho que seria legal começar por essa classe pra criar os testes, 
// e realmente tentar seguir as coisas do livro, pra ver se aprendo 
// fazendo. 