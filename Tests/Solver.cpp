#include "catch.hpp"

#include "catch.hpp"

#include <Parser.hpp>
#include <Simplifier.hpp>
#include <Solver.hpp>
#include <Utils.hpp>

#include <cmath>

TEST_CASE("<Solver><InvalidEquation>")
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
    const auto input = Simplifier::simplify(pair);
    REQUIRE(input.size() == 1);
    REQUIRE(Utils::eq(input.at(0).m_coefficient, -10));
    REQUIRE(rhs.at(0).m_power == 0);
    REQUIRE_NOTHROW(Solver::solve(input));
    const auto result = Solver::solve(input);
    REQUIRE(result.first.empty());
    REQUIRE(result.second == Solver::Result::InvalidEquation);
}

TEST_CASE("<Solver><ValidEquationNoX>")
{
    const auto test = "10=10";
    REQUIRE_NOTHROW(Parser::parse(test));
    const auto pair = Parser::parse(test);
    const auto& lhs = pair.first;
    REQUIRE(lhs.size() == 1);
    REQUIRE(Utils::eq(lhs.at(0).m_coefficient, 10));
    REQUIRE(lhs.at(0).m_power == 0);
    const auto& rhs = pair.second;
    REQUIRE(rhs.size() == 1);
    REQUIRE(Utils::eq(rhs.at(0).m_coefficient, 10));
    REQUIRE(rhs.at(0).m_power == 0);
    REQUIRE_NOTHROW(Simplifier::simplify(pair));
    const auto input = Simplifier::simplify(pair);
    REQUIRE(input.size() == 1);
    REQUIRE(Utils::eq(input.at(0).m_coefficient, 0));
    REQUIRE(rhs.at(0).m_power == 0);
    REQUIRE_NOTHROW(Solver::solve(input));
    const auto result = Solver::solve(input);
    REQUIRE(result.first.empty());
    REQUIRE(result.second == Solver::Result::ValidEquationNoX);
}

TEST_CASE("<Solver><OneRoot>")
{
    const auto test = "2x=10";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto pair = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(pair.first.size() == 1);
    REQUIRE(Utils::eq(pair.first.at(0), 5));
    REQUIRE(pair.second == Solver::Result::OneRoot);
}

TEST_CASE("<Solver><OneRoot><ZeroD>")
{
    const auto test = "x2-2x+1=0";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto pair = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(pair.first.size() == 1);
    REQUIRE(Utils::eq(pair.first.at(0), 1));
    REQUIRE(pair.second == Solver::Result::OneRoot);
}

TEST_CASE("<Solver><OneRoot><LessThanZeroD>")
{
    const auto test = "x2-x+1=0";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto pair = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(pair.first.empty());
    REQUIRE(pair.second == Solver::Result::NoRoots);
}

TEST_CASE("<Solver><OneRoot><BiggerThanZeroD>")
{
    const auto test = "x2-3x+1=0";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto pair = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(pair.first.size() == 2);
    REQUIRE(Utils::eq(pair.first.at(0), (3.0 / 2) - (std::sqrt(5) / 2)));
    REQUIRE(Utils::eq(pair.first.at(1), (3.0 / 2) + (std::sqrt(5) / 2)));
    REQUIRE(pair.second == Solver::Result::TwoRoots);
}
