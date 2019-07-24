#include "catch.hpp"

#include <Solver.hpp>
#include <Parser.hpp>

namespace {

bool eq(const double a, const double b)
{
    static constexpr auto e = 0.00001;
    return a - b < e || b - e < e;
}

}

TEST_CASE("<Solver><Infinite>")
{
    const auto p_solution = Solver::solve({0, 0, 0});
    const auto roots = p_solution->get();
    REQUIRE(roots.empty());
    REQUIRE(dynamic_cast<const Infinite*>(p_solution.get()));
}

TEST_CASE("<Solver><One>")
{
    const auto p_solution = Solver::solve(Parser::parse("5 * X^0 + 4 * X^1 = 4 * X^0"));
    const auto roots = p_solution->get();
    REQUIRE(roots.size() == 1);
    REQUIRE(roots[0] == -0.25);
    REQUIRE(dynamic_cast<const OneRoot*>(p_solution.get()));
}

TEST_CASE("<Solver><Two>")
{
    const auto p_solution = Solver::solve(Parser::parse("5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"));
    const auto roots = p_solution->get();
    REQUIRE(roots.size() == 2);
    REQUIRE(eq(roots[0], 0.905239));
    REQUIRE(eq(roots[1], -0.475131));
    REQUIRE(dynamic_cast<const TwoRoots*>(p_solution.get()));
}
