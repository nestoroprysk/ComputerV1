#include "Shower.hpp"
#include "Utils.hpp"

namespace {

void showChunk(const Chunk& i_chunk)
{
    std::cout << (i_chunk.m_coefficient < 0 ? " " : " +") <<
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
    if (i_simplified.empty())
        std::cout << " 0";
    for (const auto& c : i_simplified)
        showChunk(c);
    std::cout << " = 0" << std::endl;
    return i_simplified;
}

const Adapter::Input& Shower::show(const Adapter::Input& i_input)
{
    using namespace Adapter;
    std::cout << "Degree: ";
    std::visit(Utils::overloaded {
        [](const VoidInput&) { std::cout << "void"; },
        [](const JustNonZeroNumber&) { std::cout << "zero"; },
        [](const OneDegree&) { std::cout << "one"; },
        [](const TwoDegree&) { std::cout << "two"; },
        [](auto) { throw std::logic_error("Invalid type for the visit"); }
    }, i_input);
    std::cout << std::endl;
    return i_input;
}

const Solver::Result& Shower::show(const Solver::Result& i_solution)
{
    using namespace Solver;
    std::cout << "Result: ";
    std::visit(Utils::overloaded {
        [](const AnyRationalNumber&) { std::cout << "any rational number satisfies the equation"; },
        [](const InvalidEquation& i_sol) { std::cout << "invalid equation [" << i_sol.m_c << " = 0]"; },
        [](const JustImaginaryRoots& i_sol) { std::cout << "No real roots, imaginary [" <<
            std::to_string(i_sol.m_a) << " +" << std::to_string(i_sol.m_i_coefficient)  << " * i] and [" <<
            std::to_string(i_sol.m_a) << ' ' << std::to_string(-i_sol.m_i_coefficient) << " * i]"; },
        [](const OneRoot& i_sol) { std::cout << "single root found [" << i_sol.m_root << ']'; },
        [](const TwoRoots& i_sol) { std::cout << "two roots found [" << i_sol.m_smaller << "] and [" << i_sol.m_bigger << ']'; },
        [](auto) { throw std::logic_error("Invalid type for the visit"); }
    }, i_solution);
    std::cout << std::endl;
    return i_solution;
}
