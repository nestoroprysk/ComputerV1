#include "Utils.hpp"

#include <string>

namespace {

double halve(const double a)
{
    return a / 2.0;
}

bool closeEnough(double a, double b)
{
   return Utils::abs(a - b) < Utils::g_e;
}

double betterGuess(double x, double g) {
   return halve(g + x / g);
}

double guess(double x, double g, std::size_t nbCyclesLeft)
{
    if (!nbCyclesLeft) throw std::logic_error("sqrt(), failed to find the root of [" +
        std::to_string(x) + ']');
    return closeEnough(x / g, g) ? g : guess(x, betterGuess(x, g), nbCyclesLeft - 1);
}

}

bool Utils::eq(const double a, const double b, const double e)
{
    return Utils::abs(a - b) < e || Utils::abs(b - a) < e;
}

double Utils::sqrt(const double a)  
{
    if (a < 0) throw std::logic_error("sqrt(), possitive number expected");
    if (Utils::eq(a, 0)) return a;
    const auto nbCycles = 10000;
    return guess(a, halve(a), nbCycles);
}
