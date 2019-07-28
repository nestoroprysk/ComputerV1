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
