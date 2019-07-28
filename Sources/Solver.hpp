#pragma once

#include "Chunk.hpp"
#include "Adapter.hpp"

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

struct AnyRationalNumber{};
struct InvalidEquation{double m_c;};
struct NoRoots{};
struct OneRoot{double m_root;};
struct TwoRoots{double m_smaller; double m_bigger;};
using Result = std::variant<AnyRationalNumber, InvalidEquation, NoRoots, OneRoot, TwoRoots>;

Result solve(const Adapter::Input& i_input);

}
