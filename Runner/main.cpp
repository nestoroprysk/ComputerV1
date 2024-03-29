#include <Parser.hpp>
#include <Simplifier.hpp>
#include <Adapter.hpp>
#include <Solver.hpp>
#include <Shower.hpp>

#include <iostream>

namespace {

static constexpr auto g_usage = R"(
noprysk, 2019

Usage:
    ./Run "chunk op chunk ... op chunk = chunk"

where
    a chunk is in one of the forms:
        a: a * x ^ n
        b: a * x
        c: ax ^ n
        d: x ^ n
        e: axn
        f: ax
        g: xn
        h: x
        i: a

        where
            a is a double
            x is a char x or X
            n is an unsigned number

    an op is + or -

)";

void printError(const std::string& i_error)
{
    static constexpr auto g_error_format = "\033[1;31m";
    static constexpr auto g_normal_format = "\033[0m";
    std::cout << g_error_format << "Error: " << i_error << g_normal_format << std::endl;
}

}

int main(const int argc, const char** argv)
{
    try{
        if (argc != 2)
            throw Parser::ParseError("Simple argument expected, got [" + std::to_string(argc - 1) + ']');
        using namespace Shower;
        show(Solver::solve(show(Adapter::adopt(show(Simplifier::simplify(show(Parser::parse(argv[1]))))))));
    }
    catch (const Parser::ParseError& e){
        printError(e.what());
        std::cerr << g_usage << std::endl;
    }
    catch (const Solver::ComputationError& e){
        printError(e.what());
    }
    catch (const std::logic_error& e){
        printError(e.what());
    }
    catch (...){
        printError("Unexpected exception met");
    }
}
