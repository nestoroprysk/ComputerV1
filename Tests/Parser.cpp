#include "catch.hpp"

#include <Parser.hpp>
#include <Utils.hpp>

TEST_CASE("<Parser><I><eq><I>")
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

TEST_CASE("<Parser><C><eq><C>")
{ 
    const auto test = "10x^2=20x^1";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 1);
}

TEST_CASE("<Parser><F><Minus><I><eq><I>")
{
    const auto test = "-2x-10=20";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 2);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, -2));
    REQUIRE(lhs.at(0).m_power == 1);
    REQUIRE(Utils::eq(lhs.at(1).m_coefficient, -10));
    REQUIRE(lhs.at(1).m_power == 0);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Parser><H><eq><I>")
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

TEST_CASE("<Parser><G><eq><I>")
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

TEST_CASE("<Parser><F><eq><I>")
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

TEST_CASE("<Parser><E><eq><I>")
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

TEST_CASE("<Parser><D><eq><I>")
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

TEST_CASE("<Parser><B><eq><I>")
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

TEST_CASE("<Parser><A><eq><I>")
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

TEST_CASE("<Parser><A><Plus><B><eq><I>")
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

TEST_CASE("<Parser><A><Minus><B><eq><I>")
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

TEST_CASE("<Parser><A><Minus><B><eq><D><Minus><E>")
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

TEST_CASE("<Parser><A><Minus><B><Plus><F><eq><D><Minus><E><Plus><G>")
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

TEST_CASE("<Parser><A><Minus><D><Minus><G><eq><A><Minus><A><Minus><H>")
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

TEST_CASE("<Parser><Invalid><Empty>")
{
    const auto test = "";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><NoEq>")
{
    const auto test = "10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><TwoEqs>")
{
    const auto test = "10=10=20";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><InvalidSymbol>")
{
    const auto test = "10=10s";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><UnexpectedDotPosition>")
{
    const auto test = "10=.-10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><TwoDotsAtTheEnd>")
{
    const auto test = "10=10..";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><TwoXs>")
{
    const auto test = "10xx=10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><UnexpectedStarPosition>")
{
    const auto test = "1*0=10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><UnexpectedPowPosition>")
{
    const auto test = "1^0=10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><TwoPows>")
{
    const auto test = "x^^0=10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><NothingOnTheLeft>")
{
    const auto test = "=10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><NothingOnTheRight>")
{
    const auto test = "10=";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><PlusBeforePower>")
{
    const auto test = "x^+10=10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><MinusBeforePower>")
{
    const auto test = "x^-10=10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><TwoPluses>")
{
    const auto test = "++10=10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><TwoMinuses>")
{
    const auto test = "--10=10";
    REQUIRE_THROWS(Parser::parse(test));
}

TEST_CASE("<Parser><Invalid><Next>")
{
    const auto test = "10=10";
    REQUIRE_NOTHROW(Parser::parse(test));
}
