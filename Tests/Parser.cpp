#include "catch.hpp"

#include <Parser.hpp>

TEST_CASE("<Parser><Valid>")
{
    const auto test = "5 * X^0 + 4 * X^1 = 4 * X^0";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto result = Parser::parse(test);
    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == 0);
    REQUIRE(result[1] == 4);
    REQUIRE(result[2] == 1);
}

TEST_CASE("<Parser><Invalid><Form>")
{
    const auto test = "5 * X^0 + 4 * X^1 = 4 * X^";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><=>")
{
    const auto test = "5 * X^0 + 4 * X^1 4 * X^2";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><Symbol>")
{
    const auto test = "5 * X^0 +| 4 * X^1 = 4 * X^2";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><DoubleOperator>")
{
    const auto test = "5 * X^0 ++ 4 * X^1 = 4 * X^2";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><NoStar>")
{
    const auto test = "5 X^0 + 4 * X^1 = 4 * X^2";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><NoX>")
{
    const auto test = "5 * ^0 + 4 * X^1 = 4 * X^2";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><NoPower>")
{
    const auto test = "5 * X  0 + 4 * X^1 = 4 * X^2";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><NoPowerValue>")
{
    const auto test = "5 * X ^  + 4 * X^1 = 4 * X^2";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><NoCoefficientBegin>")
{
    const auto test = "* X ^ 2 + 4 * X^1 = 4 * X^2";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><NoCoefficientMid>")
{
    const auto test = "2 * X ^ 2 + * X^1 = 4 * X^2";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><BiggerPower>")
{
    const auto test = "2 * X ^ 2 + 2 * X^1 = 4 * X^22";
    REQUIRE_THROWS(Parser::parse(test));
}
