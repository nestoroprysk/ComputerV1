#include "Utils.hpp"

namespace {

static constexpr auto e = static_cast<double>(0.000001);

double halve(const double a)
{
    return a / 2.0;
}

bool closeEnough(double a, double b)
{
   return Utils::abs(a - b) < e;
}

double betterGuess(double x, double g) {
   return halve(g + x / g);
}

double guess(double x, double g)
{
    return closeEnough(x / g, g) ? g : guess(x, betterGuess(x, g));
}

}

bool Utils::eq(const double a, const double b)
{
    return Utils::abs(a - b) < e || Utils::abs(b - a) < e;
}

double Utils::sqrt(const double a)
{
    return guess(a, halve(a));
}

std::size_t Utils::findBiggestDegree(const std::vector<Chunk>& i_input)
{
    auto result = std::size_t(0);
    for (const auto& c : i_input)
        // TODO: uncomment if and fix the Solver
        // if (!eq(c.m_coefficient, 0))
            result = max(result, c.m_power);
    return result;
}
