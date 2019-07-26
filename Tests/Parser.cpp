#include "catch.hpp"

#include <Parser.hpp>
#include <Utils.hpp>

TEST_CASE("<Parser><h><eq><h>")
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

TEST_CASE("<Parser><g><eq><h>")
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

TEST_CASE("<Parser><f><eq><h>")
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

TEST_CASE("<Parser><e><eq><h>")
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

TEST_CASE("<Parser><d><eq><h>")
{
    const auto test = "10x2=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Parser><c><eq><h>")
{
    const auto test = "x^2=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 1));
    REQUIRE(lhs.at(0).m_power == 2);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Parser><b><eq><h>")
{
    const auto test = "10*x=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 1);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Parser><a><eq><h>")
{
    const auto test = "10*x^2=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Parser><a><Plus><b><eq><h>")
{
    const auto test = "10*x^2+20*x=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 2);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(lhs.at(1).m_coefficient, 20));
    REQUIRE(lhs.at(1).m_power == 1);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Parser><a><Minus><b><eq><h>")
{
    const auto test = "10*x^2-20*x=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 2);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(lhs.at(1).m_coefficient, -20));
    REQUIRE(lhs.at(1).m_power == 1);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Parser><a><Minus><b><eq><c><Minus><d>")
{
    const auto test = "10*x^2-20*x=x^2-3x2";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 2);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(lhs.at(1).m_coefficient, -20));
    REQUIRE(lhs.at(1).m_power == 1);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 2);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 1));
    REQUIRE(rhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(rhs.at(1).m_coefficient, -3));
    REQUIRE(rhs.at(1).m_power == 2);
}

TEST_CASE("<Parser><a><Minus><b><Plus><e><eq><c><Minus><d><Plus><f>")
{
    const auto test = "10*x^2-20*x+4x=x^2-3x2+x3";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 3);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(lhs.at(1).m_coefficient, -20));
    REQUIRE(lhs.at(1).m_power == 1);
    REQUIRE(Utils::eq(lhs.at(2).m_coefficient, 4));
    REQUIRE(lhs.at(2).m_power == 1);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 3);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 1));
    REQUIRE(rhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(rhs.at(1).m_coefficient, -3));
    REQUIRE(rhs.at(1).m_power == 2);
    REQUIRE(Utils::eq(rhs.at(2).m_coefficient, 1));
    REQUIRE(rhs.at(2).m_power == 3);
}

TEST_CASE("<Parser><a><Minus><c><Minus><f><eq><a><Minus><a><Minus><g>")
{
    const auto test = "-5*x^2-x^1-x2=+10*x^3-5*x^2-x";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 3);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, -5));
    REQUIRE(lhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(lhs.at(1).m_coefficient, -1));
    REQUIRE(lhs.at(1).m_power == 1);
    REQUIRE(Utils::eq(lhs.at(2).m_coefficient, -1));
    REQUIRE(lhs.at(2).m_power == 2);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 3);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 10));
    REQUIRE(rhs.at(0).m_power == 3);
    REQUIRE(Utils::eq(rhs.at(1).m_coefficient, -5));
    REQUIRE(rhs.at(1).m_power == 2);
    REQUIRE(Utils::eq(rhs.at(2).m_coefficient, -1));
    REQUIRE(rhs.at(2).m_power == 1);
}
