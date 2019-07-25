#include "catch.hpp"

#include <Parser.hpp>
#include <Utils.hpp>

TEST_CASE("<Parser><h>")
{
    const auto test = "10=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 0);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Parser><g>")
{
    const auto test = "x=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 1));
    REQUIRE(lhs.at(0).m_power == 1);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Parser><f>")
{
    const auto test = "x10=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 1));
    REQUIRE(lhs.at(0).m_power == 10);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Parser><e>")
{
    const auto test = "2x=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 2));
    REQUIRE(lhs.at(0).m_power == 1);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}
