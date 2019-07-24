#include "Solver.hpp"
#include <iostream>
#include <cmath>

std::unique_ptr<ISolution> Solver::solve(const std::array<double, 3>& i_input)
{
    const auto a = i_input.at(0);
    const auto b = i_input.at(1);
    const auto c = i_input.at(2);
    
    const auto d = b * b - 4 * a * c;

    if (a == 0){
        if (b == 0)
            return std::make_unique<Infinite>();
        const auto x = -c / b;
        return std::make_unique<OneRoot>(x);
    }

    if (d == 0){
        const auto x = -b / 2 * a;
        return std::make_unique<OneRoot>(x);
    }

    if (d > 0){
        const auto x1 = (-b - std::sqrt(d)) / (2 * a);
        const auto x2 = (-b + std::sqrt(d)) / (2 * a);
        return std::make_unique<TwoRoots>(x1, x2);
    }

    if (d < 0){
        return std::make_unique<NoSolution>();
    }

    return {};
}
