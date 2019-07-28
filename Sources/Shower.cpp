#include "Shower.hpp"
#include "Utils.hpp"

#include <iostream>

void Shower::show(const Solver::Result& i_solution)
{
	using namespace Solver;
    std::visit(Utils::overloaded {
        [](const InvalidEquation&) { std::cout << "Invalid equation" << std::endl; },
        [](const ValidEquationNoX&) { std::cout << "Valid equation without X" << std::endl; },
        [](const InfiniteRoots&) { std::cout << "Any rational X satisfies the equation" << std::endl; },
        [](const OneRoot& i_sol) { std::cout << "Single root found: [" << i_sol.m_root << ']' << std::endl; },
        [](const TwoRoots& i_sol) { std::cout << "Two roots found: [" << i_sol.m_smaller << "] and [" << i_sol.m_bigger << ']' << std::endl; },
        [](const NoRoots&) { std::cout << "No roots found" << std::endl; },
        [](auto) { throw std::logic_error("Invalid type for the visit"); }
    }, i_solution);
}
