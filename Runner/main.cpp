#include <Parser.hpp>

#include <iostream>

static constexpr auto g_usage = R"(
noprysk, 2019

Usage:
    ./Run "chunk op chunk ... op chunk = chunk"

where
    a chunk is in one of the forms:
        a: a * x ^ n
        b: a * x
        c: x ^ n
        d: axn
        e: ax
        f: xn
        g: x
        h: a

        where
            a is a double
            x is a char x or X
            n is an unsigned number

    an op is + or -

)";

int main()
{
    try{
        throw Parser::ParseError("show(solve(simplify(parse())))");
    }
    catch (const Parser::ParseError& e){
        std::cerr << std::endl << "Error: " << e.what() << std::endl;
        std::cerr << g_usage << std::endl;
    }
}
