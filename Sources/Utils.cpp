#include "Utils.hpp"

#include <cmath>

bool Utils::eq(const double a, const double b, const double e)
{
    return Utils::abs(a - b) < e || Utils::abs(b - a) < e;
}

double Utils::sqrt(const double a)  
{
    return std::sqrt(a);
}
