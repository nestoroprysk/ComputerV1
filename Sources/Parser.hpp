#pragma once

#include "Chunk.hpp"

#include <string>
#include <vector>

namespace Parser {

std::pair<std::vector<Chunk>, std::vector<Chunk>> parse(const std::string& s);

class ParseError : public std::exception
{
public:
    ParseError(const std::string i_error) : m_error(i_error){}
    const char* what() const noexcept override{ return m_error.c_str(); }
private:
    const std::string m_error;
};

}
