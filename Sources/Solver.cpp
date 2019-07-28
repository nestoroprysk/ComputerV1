#include "Solver.hpp"
#include "Utils.hpp"

namespace {

using namespace Solver;

std::size_t findBiggestPower(const std::vector<Chunk>& i_input)
{
    auto result = std::size_t(0);
    for (const auto& c : i_input)
        result = std::max(result, c.m_power);
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

namespace SolverDetail {

// a = 0
const auto a = [](const std::vector<Chunk>& i_input) -> Result{
    // TODO: assert
    return Utils::eq(getCoefficient<0>(i_input), 0)
        ? Result{ValidEquationNoX{}}
        :  Result{InvalidEquation{}};
};

// x + a = 0
// x = 0
const auto b = [](const std::vector<Chunk>& i_input) -> Result{
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
    if (Utils::eq(a, 0)) throw std::logic_error("c(input), (a) cannot be zero");
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
    return Result{TwoRoots{std::min(x1, x2), std::max(x1, x2)}};
};

}

}

Result Solver::solve(const std::vector<Chunk>& i_input)
{
    if (i_input.empty()) throw ComputationError("Non-empty input expected");
    const auto biggestPower = findBiggestPower(i_input);
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
