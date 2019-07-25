#pragma once

#include "Chunk.hpp"

#include <vector>
#include <array>

namespace Adapter {

std::array<double, 3> adopt(const std::pair<std::vector<Chunk>, std::vector<Chunk>>& i_input);

}
