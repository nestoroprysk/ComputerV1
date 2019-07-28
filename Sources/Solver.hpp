#pragma once

#include "Chunk.hpp"

#include <string>
#include <vector>
#include <variant>

namespace Solver{

class ComputationError : public std::exception
{
public:
    ComputationError(const std::string i_error) : m_error(i_error){}
    const char* what() const noexcept override{ return m_error.c_str(); }
private:
    const std::string m_error;
};

struct InvalidEquation{};
struct InfiniteRoots{};
struct OneRoot{const double m_root;};
struct TwoRoots{const double m_smaller; const double m_bigger;};
struct NoRoots{};
using Result = std::variant<InvalidEquation, InfiniteRoots, OneRoot, TwoRoots, NoRoots>;
Result solve(const std::vector<Chunk>& i_input);

}
