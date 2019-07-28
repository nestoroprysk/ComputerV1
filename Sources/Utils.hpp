#pragma once

#include "Chunk.hpp"

#include <vector>

namespace Utils {

static constexpr auto g_e = static_cast<double>(0.00001);

bool eq(const double a, const double b, const double e = g_e);

// implemented for the restrains of the subject
template <typename T>
T abs(const T& i_val) { return i_val >= 0 ? i_val : -i_val; }

// implemented for the restrains of the subject
template <typename T>
constexpr T min(const T& i_lhs, const T& i_rhs) { return i_lhs > i_rhs ? i_rhs : i_lhs; }

// implemented for the restrains of the subject
template <typename T>
constexpr T max(const T& i_lhs, const T& i_rhs) { return i_lhs > i_rhs ? i_lhs : i_rhs; }

// implemented for the restrains of the subject
double sqrt(const double a);

// taken from https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

}
