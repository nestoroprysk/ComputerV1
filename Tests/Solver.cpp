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
    REQUIRE(std::holds_alternative<Solver::InvalidEquation>(result));
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
    REQUIRE(std::holds_alternative<Solver::ValidEquationNoX>(result));
}

TEST_CASE("<Solver><OneRoot>")
{
    const auto test = "2x=10";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Solver::OneRoot>(result));
    std::visit(Utils::overloaded {
        [](const Solver::OneRoot& i_solution) { REQUIRE(Utils::eq(i_solution.m_root, 5)); },
        [](auto) { REQUIRE(!"Invalid visit"); }
    }, result);
}

TEST_CASE("<Solver><OneRoot><ZeroD>")
{
    const auto test = "x2-2x+1=0";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Solver::OneRoot>(result));
    std::visit(Utils::overloaded {
        [](const Solver::OneRoot& i_solution) { REQUIRE(Utils::eq(i_solution.m_root, 1)); },
        [](auto) { REQUIRE(!"Invalid visit"); }
    }, result);
}

TEST_CASE("<Solver><OneRoot><LessThanZeroD>")
{
    const auto test = "x2-x+1=0";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Solver::NoRoots>(result));
}

TEST_CASE("<Solver><OneRoot><BiggerThanZeroD>")
{
    const auto test = "x2-3x+1=0";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Solver::TwoRoots>(result));
    std::visit(Utils::overloaded {
        [](const Solver::TwoRoots& i_solution){
            REQUIRE(Utils::eq(i_solution.m_smaller, (3.0 / 2) - (std::sqrt(5) / 2)));
            REQUIRE(Utils::eq(i_solution.m_bigger, (3.0 / 2) + (std::sqrt(5) / 2)));
        },
        [](auto) { REQUIRE(!"Invalid visit"); }
    }, result);
}

TEST_CASE("<Solver><InfiniteRoots><1>")
{
    const auto test = "x=x";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Solver::InfiniteRoots>(result));
}

TEST_CASE("<Solver><InfiniteRoots><2>")
{
    const auto test = "x2=x2";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Solver::InfiniteRoots>(result));
}

TEST_CASE("<Solver><InvalidEquation><1>")
{
    const auto test = "x1+2=x1";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Solver::InvalidEquation>(result));
}

TEST_CASE("<Solver><InvalidEquation><2>")
{
    const auto test = "x2+2=x2";
    REQUIRE_NOTHROW(Solver::solve(
        Simplifier::simplify(
            Parser::parse(test))));
    const auto result = Solver::solve(
        Simplifier::simplify(
            Parser::parse(test)));
    REQUIRE(std::holds_alternative<Solver::InvalidEquation>(result));
}
