#pragma once

#include "Chunk.hpp"

#include <string>
#include <vector>

namespace Solver{

class ComputationError : public std::exception
{
public:
    ComputationError(const std::string i_error) : m_error(i_error){}
    const char* what() const noexcept override{ return m_error.c_str(); }
private:
    const std::string m_error;
};

enum class Result { InvalidEquation, ValidEquationNoX, InfiniteRoots, OneRoot, TwoRoots, NoRoots };

std::pair<std::vector<double>, Result>
solve(const std::vector<Chunk>& i_input);

}
