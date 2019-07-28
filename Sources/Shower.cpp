#include "Shower.hpp"
#include "Utils.hpp"

#include <iostream>

namespace {

void showChunk(const Chunk& i_chunk)
{
    std::cout << ' ' << (i_chunk.m_coefficient <= 0 ? '-' : '+') <<
        i_chunk.m_coefficient << "x^" << i_chunk.m_power;
}

}

const std::pair<std::vector<Chunk>, std::vector<Chunk>>& Shower::show(const std::pair<std::vector<Chunk>, std::vector<Chunk>>& i_parsed)
{
    std::cout << "Parsed:";
    for (const auto& c : i_parsed.first)
        showChunk(c);
    std::cout << " =";
    for (const auto& c : i_parsed.second)
        showChunk(c);
    std::cout << std::endl;
    return i_parsed;
}

const std::vector<Chunk>& Shower::show(const std::vector<Chunk>& i_simplified)
{
    std::cout << "Simplified:";
    for (const auto& c : i_simplified)
        showChunk(c);
    std::cout << "= 0" << std::endl;
    return i_simplified;
}

const Solver::Result& Shower::show(const Solver::Result& i_solution)
{
    using namespace Solver;
    std::cout << "Result: ";
    std::visit(Utils::overloaded {
        [](const InvalidEquation&) { std::cout << "invalid equation" << std::endl; },
        [](const ValidEquationNoX&) { std::cout << "valid equation without X" << std::endl; },
        [](const InfiniteRoots&) { std::cout << "any rational X satisfies the equation" << std::endl; },
        [](const OneRoot& i_sol) { std::cout << "single root found [" << i_sol.m_root << ']' << std::endl; },
        [](const TwoRoots& i_sol) { std::cout << "two roots found [" << i_sol.m_smaller << "] and [" << i_sol.m_bigger << ']' << std::endl; },
        [](const NoRoots&) { std::cout << "No roots found" << std::endl; },
        [](auto) { throw std::logic_error("Invalid type for the visit"); }
    }, i_solution);
    return i_solution;
}
