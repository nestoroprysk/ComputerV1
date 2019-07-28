#pragma once

#include <cmath>

namespace Utils {

static constexpr auto g_all_real_numbers = std::numeric_limits<double>::max();

inline bool eq(const double a, const double b)
{
    static constexpr auto e = static_cast<double>(0.000001);
    return std::abs(a - b) < e || std::abs(b - a) < e;
}

inline double sqrt(const double a)
{
    return std::sqrt(a);
}

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

}
