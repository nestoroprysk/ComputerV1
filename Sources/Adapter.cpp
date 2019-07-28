#include "Adapter.hpp"

#include "Utils.hpp"
#include "Solver.hpp"

namespace {

std::size_t findBiggestDegree(const std::vector<Chunk>& i_input)
{
    auto result = std::size_t(0);
    for (const auto& c : i_input)
        result = Utils::max(result, c.m_power);
    return result;
}

template <std::size_t i_power>
double getCoefficient(const std::vector<Chunk>& i_input)
{
    for (const auto& c : i_input)
        if (c.m_power == i_power)
            return c.m_coefficient;
    throw std::logic_error("find(input, pow), no element with pow eq [" +
                std::to_string(i_power) + "] found");
}

template <std::size_t i_power>
double getCoefficientOr(const std::vector<Chunk>& i_input, const double i_alternative)
{
    for (const auto& c : i_input)
        if (c.m_power == i_power)
            return c.m_coefficient;
    return i_alternative;
}

}

Adapter::Input Adapter::adopt(const std::vector<Chunk> i_input)
{
    if (i_input.empty()) return VoidInput{};
    const auto biggestDegree = findBiggestDegree(i_input);
    switch (biggestDegree){
        case 0: return JustNonZeroNumber{getCoefficient<0>(i_input)};
        case 1: return OneDegree{getCoefficient<1>(i_input), getCoefficientOr<0>(i_input, 0)};
        case 2: return TwoDegree{getCoefficient<2>(i_input), getCoefficientOr<1>(i_input, 0), getCoefficientOr<0>(i_input, 0)};
        default: throw Solver::ComputationError("Expected power within the range [0, 1], got ["
            + std::to_string(biggestDegree) + ']');
    }
}
