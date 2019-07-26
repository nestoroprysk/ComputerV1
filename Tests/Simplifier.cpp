#include "catch.hpp"

#include <Parser.hpp>
#include <Simplifier.hpp>
#include <Utils.hpp>

TEST_CASE("<Simplifier><0><two>")
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
    REQUIRE_NOTHROW(Simplifier::simplify(pair));
    const auto result = Simplifier::simplify(pair);
    REQUIRE(result.size() == 1);
    REQUIRE(Utils::eq(result.at(0).m_coefficient, -10));
    REQUIRE(rhs.at(0).m_power == 0);
}

TEST_CASE("<Simplifier><1><two>")
{
    const auto test = "10x=20x";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 1);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 1);
    REQUIRE_NOTHROW(Simplifier::simplify(pair));
    const auto result = Simplifier::simplify(pair);
    REQUIRE(result.size() == 1);
    REQUIRE(Utils::eq(result.at(0).m_coefficient, -10));
    REQUIRE(rhs.at(0).m_power == 1);
}

TEST_CASE("<Simplifier><2><two>")
{
    const auto test = "10x2=20x2";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 2);
    REQUIRE_NOTHROW(Simplifier::simplify(pair));
    const auto result = Simplifier::simplify(pair);
    REQUIRE(result.size() == 1);
    REQUIRE(Utils::eq(result.at(0).m_coefficient, -10));
    REQUIRE(rhs.at(0).m_power == 2);
}

TEST_CASE("<Simplifier><2><three>")
{
    const auto test = "10x2=20x2+50x2";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 2);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(rhs.at(1).m_coefficient, 50));
    REQUIRE(rhs.at(1).m_power == 2);
    REQUIRE_NOTHROW(Simplifier::simplify(pair));
    const auto result = Simplifier::simplify(pair);
    REQUIRE(result.size() == 1);
    REQUIRE(Utils::eq(result.at(0).m_coefficient, -60));
    REQUIRE(rhs.at(0).m_power == 2);
}


TEST_CASE("<Simplifier><2><four>")
{
    const auto test = "10x2-3x2=20x2+50x2";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 2);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(lhs.at(1).m_coefficient, -3));
    REQUIRE(lhs.at(1).m_power == 2);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 2);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(rhs.at(1).m_coefficient, 50));
    REQUIRE(rhs.at(1).m_power == 2);
    REQUIRE_NOTHROW(Simplifier::simplify(pair));
    const auto result = Simplifier::simplify(pair);
    REQUIRE(result.size() == 1);
    REQUIRE(Utils::eq(result.at(0).m_coefficient, -63));
    REQUIRE(result.at(0).m_power == 2);
}

TEST_CASE("<Simplifier><2><1><four>")
{
    const auto test = "10x2-3x=20x2+50x2";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 2);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(lhs.at(1).m_coefficient, -3));
    REQUIRE(lhs.at(1).m_power == 1);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 2);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(rhs.at(1).m_coefficient, 50));
    REQUIRE(rhs.at(1).m_power == 2);
    REQUIRE_NOTHROW(Simplifier::simplify(pair));
    const auto result = Simplifier::simplify(pair);
    REQUIRE(result.size() == 2);
    REQUIRE(Utils::eq(result.at(0).m_coefficient, -3));
    REQUIRE(result.at(0).m_power == 1);
    REQUIRE(Utils::eq(result.at(1).m_coefficient, -60));
    REQUIRE(result.at(1).m_power == 2);
}

TEST_CASE("<Simplifier><2><1><0><six>")
{
    const auto test = "10x2-3x-6=20x2+50x2+2";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 3);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(lhs.at(1).m_coefficient, -3));
    REQUIRE(lhs.at(1).m_power == 1);
    REQUIRE(Utils::eq(lhs.at(2).m_coefficient, -6));
    REQUIRE(lhs.at(2).m_power == 0);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 3);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 20));
    REQUIRE(rhs.at(0).m_power == 2);
    REQUIRE(Utils::eq(rhs.at(1).m_coefficient, 50));
    REQUIRE(rhs.at(1).m_power == 2);
    REQUIRE(Utils::eq(rhs.at(2).m_coefficient, 2));
    REQUIRE(rhs.at(2).m_power == 0);
    REQUIRE_NOTHROW(Simplifier::simplify(pair));
    const auto result = Simplifier::simplify(pair);
    REQUIRE(result.size() == 3);
    REQUIRE(Utils::eq(result.at(0).m_coefficient, -8));
    REQUIRE(result.at(1).m_power == 1);
    REQUIRE(Utils::eq(result.at(1).m_coefficient, -3));
    REQUIRE(result.at(1).m_power == 1);
    REQUIRE(Utils::eq(result.at(2).m_coefficient, -60));
    REQUIRE(result.at(2).m_power == 2);
}
