#pragma once

#include "Parser.hpp"
#include "Simplifier.hpp"
#include "Adapter.hpp"
#include "Solver.hpp"

namespace Shower {

const std::pair<std::vector<Chunk>, std::vector<Chunk>>& show(const std::pair<std::vector<Chunk>, std::vector<Chunk>>& i_parsed);
const std::vector<Chunk>& show(const std::vector<Chunk>& i_simplified);
const Adapter::Input& show(const Adapter::Input& i_input);
const Solver::Result& show(const Solver::Result& i_solution);

}
