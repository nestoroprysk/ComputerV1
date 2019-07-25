#include <Parser.hpp>

#include <iostream>

static constexpr auto g_usage = R"(
noprysk, 2019

Usage:
    ./Run "chunk_0 op chunk_1 ... op chunk_n = chunk_0_1"

where a chunk is:
    a: a * x ^ n
    b: a * x
    c: x ^ n
    d: axn
    e: ax
    f: xn
    g: x
    h: a

where op is:
    a. +
    b. -
)";

int main()
{
    try{
        throw Parser::ParseError("show(solve(adopt(parse())))");
    }
    catch (const Parser::ParseError& e){
        std::cerr << std::endl << "Error: " << e.what() << std::endl;
        std::cerr << g_usage << std::endl;
    }
}
