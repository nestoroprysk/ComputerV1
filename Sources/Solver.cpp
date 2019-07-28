#include "Solver.hpp"
#include "Utils.hpp"

namespace {

using namespace Solver;

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

namespace SolverDetail {

// a = 0
const auto a = [](const std::vector<Chunk>& i_input) -> Result{
    return Utils::eq(getCoefficient<0>(i_input), 0)
        ? Result{InfiniteRoots{}}
        :  Result{InvalidEquation{}};
};

// x + a = 0
// (a)x2 + (b)x + (c)a = 0
const auto b = [](const std::vector<Chunk>& i_input) -> Result{
    const auto b = getCoefficient<1>(i_input);
    const auto c = getCoefficientOr<0>(i_input, 0);
    if (Utils::eq(b, 0) && Utils::eq(c, 0))
        // x = x
        return Result{InfiniteRoots{}};
    if (Utils::eq(b, 0))
        return Result{InvalidEquation{}};
    const auto root = -getCoefficientOr<0>(i_input, 0) /
        getCoefficient<1>(i_input);
    return Result{OneRoot{root}};
};

// x2 + x + a = 0
// (a)x2 + (b)x + (c)a = 0
const auto c = [](const std::vector<Chunk>& i_input) -> Result{
    const auto a = getCoefficient<2>(i_input);
    const auto b = getCoefficientOr<1>(i_input, 0);
    const auto c = getCoefficientOr<0>(i_input, 0);
    const auto d = b * b - 4 * a * c;
    if (Utils::eq(a, 0) && Utils::eq(b, 0) && Utils::eq(c, 0))
        return Result{InfiniteRoots{}};
    if (Utils::eq(a, 0))
        return Result{InvalidEquation{}};
    if (Utils::eq(d, 0)){
        const auto root = -b / 2 * a;
        return Result{OneRoot{root}};
    }
    if (d < 0)
        return Result{NoRoots{}};
    // d > 0
    auto result = std::vector<double>();
    const auto x1 = (-b - Utils::sqrt(d)) / (2 * a);
    const auto x2 = (-b + Utils::sqrt(d)) / (2 * a);
    result.push_back(x1);
    result.push_back(x2);
    return Result{TwoRoots{Utils::min(x1, x2), Utils::max(x1, x2)}};
};

}

}

Result Solver::solve(const std::vector<Chunk>& i_input)
{
    if (i_input.empty()) throw ComputationError("Non-empty input expected");
    const auto biggestPower = Utils::findBiggestDegree(i_input);
    using Solver = std::function<Result(const std::vector<Chunk>& i_input)>;
    using namespace SolverDetail;
    static const auto solvers = std::vector<Solver> { a, b, c };
    try{
        return solvers.at(biggestPower)(i_input);
    }
    catch (std::out_of_range){
        throw ComputationError("Expected power within the range [0, 1], got ["
            + std::to_string(biggestPower) + ']');
    }
}
