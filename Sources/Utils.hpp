#pragma once

#include "Chunk.hpp"

#include <vector>

namespace Utils {

bool eq(const double a, const double b);

// implemented for the restrains of the subject
template <typename T>
bool abs(const T& i_val) { return i_val >= 0 ? i_val : -i_val; }

// implemented for the restrains of the subject
template <typename T>
constexpr T min(const T& i_lhs, const T& i_rhs) { return i_lhs > i_rhs ? i_rhs : i_lhs; }

// implemented for the restrains of the subject
template <typename T>
constexpr T max(const T& i_lhs, const T& i_rhs) { return i_lhs > i_rhs ? i_lhs : i_rhs; }

// implemented for the restrains of the subject
// taken from https://stackoverflow.com/questions/3581528/how-is-the-square-root-function-implemented
double sqrt(const double a);

// taken from https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

std::size_t findBiggestDegree(const std::vector<Chunk>& i_input);

}
