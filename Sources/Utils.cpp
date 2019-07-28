#include "Utils.hpp"

#include <iostream>
#include <cmath>

namespace {

static constexpr auto e = static_cast<double>(0.0001);

}

bool Utils::eq(const double a, const double b)
{
    return Utils::abs(a - b) < e || Utils::abs(b - a) < e;
}

double Utils::sqrt(const double a)
{
   return std::sqrt(a);
}
