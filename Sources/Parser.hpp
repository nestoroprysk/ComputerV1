#pragma once

#include <string>
#include <array>

class ParseError : public std::exception
{
public:
    ParseError(const std::string i_error) : m_error(i_error){}
    const char* what() const noexcept override{ return m_error.c_str(); }
private:
    const std::string m_error;
};

namespace Parser {

std::array<double, 3> parse(const std::string& s);

}
