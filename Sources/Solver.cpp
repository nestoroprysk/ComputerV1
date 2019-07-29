#include "Solver.hpp"
#include "Utils.hpp"
#include "Adapter.hpp"

namespace {

using namespace Solver;
using namespace Adapter;

// bx + c = 0
Result solveOneDegree(const OneDegree& i_input)
{
    const auto root = -i_input.m_c / i_input.m_b;
    return Result{OneRoot{root}};
};

Result solveTwoDegree(const TwoDegree& i_input)
{
    const auto d = i_input.m_b * i_input.m_b
        - 4 * i_input.m_a * i_input.m_c;
    if (Utils::eq(d, 0)){
        const auto root = -i_input.m_b / (2 * i_input.m_a);
        return Result{OneRoot{root}};
    }
    if (d < 0){
        const auto a = -i_input.m_b / (2 * i_input.m_a);
        const auto i_coefficient = Utils::abs(Utils::sqrt(Utils::abs(d)) / (2 * i_input.m_a));
        return Result{JustImaginaryRoots{a, i_coefficient}};
    }
    // d > 0
    auto result = std::vector<double>();
    const auto x1 = (-i_input.m_b - Utils::sqrt(d)) / (2 * i_input.m_a);
    const auto x2 = (-i_input.m_b + Utils::sqrt(d)) / (2 * i_input.m_a);
    result.push_back(x1);
    result.push_back(x2);
    return Result{TwoRoots{Utils::min(x1, x2), Utils::max(x1, x2)}};
};

}

Result Solver::solve(const Adapter::Input& i_input)
{
    auto result = Result{};
    std::visit(Utils::overloaded {
        [&](const VoidInput&) { result = Result{AnyRationalNumber{}}; },
        [&](const JustNonZeroNumber& i_input) { result = Result{InvalidEquation{i_input.m_c}}; },
        [&](const OneDegree& i_input) { result = solveOneDegree(i_input); },
        [&](const TwoDegree& i_input) { result = solveTwoDegree(i_input); },
        [&](auto) { throw std::logic_error("Invalid type for the visit"); }
    }, i_input);
    return result;
}
