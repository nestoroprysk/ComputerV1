#pragma once

#include "Chunk.hpp"

#include <vector>
#include <variant>

namespace Adapter{

struct VoidInput{};
struct JustNonZeroNumber{double m_c;};
struct OneDegree{const double m_b; const double m_c;};
struct TwoDegree{const double m_a; const double m_b; const double m_c;};
using Input = std::variant<VoidInput, JustNonZeroNumber, OneDegree, TwoDegree>;

Input adopt(const std::vector<Chunk> i_input);

}
