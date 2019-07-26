#pragma once

#include "Chunk.hpp"

#include <vector>

namespace Simplifier {

std::vector<Chunk>
simplify(const std::pair<std::vector<Chunk>,
    std::vector<Chunk>>& i_input);

}
