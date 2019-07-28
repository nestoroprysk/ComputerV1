#include "catch.hpp"

#include <Utils.hpp>
#include <Parser.hpp>
#include <Simplifier.hpp>
#include <Adapter.hpp>

TEST_CASE("<Adapter><VoidInput>")
{
    const auto test = "x=x";
    REQUIRE_NOTHROW(Adapter::adopt(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Adapter::adopt(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Adapter::VoidInput>(result));
}

TEST_CASE("<Adapter><JustNonZeroNumber>")
{
    const auto test = "10=0";
    REQUIRE_NOTHROW(Adapter::adopt(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Adapter::adopt(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Adapter::JustNonZeroNumber>(result));
    REQUIRE(Utils::eq(std::get<Adapter::JustNonZeroNumber>(result).m_c, 10));
}

TEST_CASE("<Adapter><OneDegree>")
{
    const auto test = "2x - 10 = 2";
    REQUIRE_NOTHROW(Adapter::adopt(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Adapter::adopt(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Adapter::OneDegree>(result));
    REQUIRE(Utils::eq(std::get<Adapter::OneDegree>(result).m_b, 2));
    REQUIRE(Utils::eq(std::get<Adapter::OneDegree>(result).m_c, -12));
}

TEST_CASE("<Adapter><TwoDegree>")
{
    const auto test = "3x2 - 2x - 10 = 2";
    REQUIRE_NOTHROW(Adapter::adopt(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Adapter::adopt(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Adapter::TwoDegree>(result));
    REQUIRE(Utils::eq(std::get<Adapter::TwoDegree>(result).m_a, 3));
    REQUIRE(Utils::eq(std::get<Adapter::TwoDegree>(result).m_b, -2));
    REQUIRE(Utils::eq(std::get<Adapter::TwoDegree>(result).m_c, -12));
}
