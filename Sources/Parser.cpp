#include "Parser.hpp"

#include <sstream>
#include <vector>

namespace {

struct Chunk
{
    double m_coefficient = 0;
    std::size_t m_power = 0;
};

const std::string& validate(const std::string& s)
{
    // empty check
    if (s.empty())
        throw ParseError("Non-empty string expected");
    
    // allowed signs check
    {
    const auto allowedSigns = std::string(".+-X^*=");
    for (const auto ch : s)
        if (!std::isdigit(ch) && allowedSigns.find(ch) == std::string::npos)
            throw ParseError(std::string("Unrecognised symbol [") + ch + ']');
    }

    // = check
    {
        const auto n = std::count(s.cbegin(), s.cend(), '=');
        if (n != 1)
            throw ParseError("Expected single [=], got " + std::to_string(n));
    }

    // special sign not end and not a few times check
    {
        const auto allowedSigns = std::string(".+-X^*=");
        for (std::size_t i = 0; i < s.size(); ++i){
            if (allowedSigns.find(s[i]) == std::string::npos)
                continue;
            if (i == s.size() - 1)
                throw ParseError(std::string("Unexpected end of input [") + s[i] + ']');
            if (s[i + 1] == s[i])
                throw ParseError(std::string("[") + s[i] + "] met a few times");
        }
    }

    // a * X ^ n form check
    for (std::size_t i = 0; i < s.size(); ++i)
        if (s[i] == '*')
            if (s.size() <= i + 2 || s[i + 1] != 'X' || s[i + 2] != '^' || i + 3 == s.size())
                throw ParseError("The form [a * X ^ n] expected");
    
    // * before X check
    for (std::size_t i = 0; i < s.size(); ++i)
        if (s[i] == 'X')
            if (i == 0 || s[i - 1] != '*')
                throw ParseError("Expected [*] before [X]");
    
    // some numeric after ^ check
    for (std::size_t i = 0; i < s.size(); ++i)
        if (s[i] == '^')
            if (i == s.size() - 1 || !std::isdigit(s[i + 1]))
                throw ParseError("Expected digit after [^]");

    // some numeric before * check
    for (std::size_t i = 0; i < s.size(); ++i)
        if (s[i] == '*')
            if (i == 0 || !std::isdigit(s[i - 1]))
                throw ParseError("Expected digit before [*]");

    return s;
}

std::string filterSpaces(const std::string s)
{
    auto result = std::string();
    for (const auto c : s)
        if (!std::isspace(c))
            result += c;
    return result;
}

std::pair<std::string, std::string> splitAt(const std::string s, const char c)
{
    const auto i = std::find(s.cbegin(), s.cend(), c);
    return {std::string(s.cbegin(), i), std::string(std::next(i), s.cend())};
}

static constexpr auto g_delim = '$';

std::string simplify(const std::string& s)
{
    auto result = std::string();
    for (const auto ch : s){
        if (ch == '*')
            result += g_delim;
        else if (ch == 'X' || ch == '^')
            continue;
        else
            result += ch;
    }
    return result;
}

template <typename T>
std::unique_ptr<T> tryGet(std::stringstream& ss)
{
    if (!ss) return {};
    auto o = T();
    ss >> o;
    if (ss.fail()) return {};
    return std::make_unique<T>(std::move(o));
}

std::unique_ptr<Chunk> tryGetChunk(std::stringstream& ss)
{
    const auto opt_coefficient = tryGet<double>(ss);
    tryGet<char>(ss);
    const auto opt_power = tryGet<std::size_t>(ss);
    if (!opt_coefficient || !opt_power)
        return {};
    if (*opt_power > 2)
        throw ParseError("Power within the range [0, 2] expected, got " + std::to_string(*opt_power));
    auto result = Chunk{*opt_coefficient, *opt_power};
    return std::make_unique<Chunk>(std::move(result));
}

std::vector<Chunk> getChunks(const std::string& s)
{
    auto result = std::vector<Chunk>();
    auto ss = std::stringstream(s);
    while (auto opt_chunk = tryGetChunk(ss))
        result.emplace_back(std::move(*opt_chunk));
    return result;
}

std::vector<Chunk> merge(const std::vector<Chunk>& i_lhs, const std::vector<Chunk>& i_rhs)
{
    auto result = std::vector<Chunk>();
    for (const auto ch : i_lhs)
        result.emplace_back(ch);
    for (auto ch : i_rhs){
        ch.m_coefficient = -ch.m_coefficient;
        result.emplace_back(std::move(ch));
    }
    return result;
}

std::array<double, 3> simplify(const std::vector<Chunk>& i_chunks)
{
    auto result = std::array<Chunk, 3>();
    result[0] = {0, 0};
    result[1] = {0, 1};
    result[2] = {0, 2};
    for (const auto c : i_chunks)
        for (auto& r : result)
            if (r.m_power == c.m_power)
                r.m_coefficient += c.m_coefficient;
    return {result[2].m_coefficient, result[1].m_coefficient,
                result[0].m_coefficient};
}

}

std::array<double, 3> Parser::parse(const std::string& s)
{
    const auto pair = splitAt(simplify(validate(filterSpaces(s))), '=');
    const auto leftChunks = getChunks(pair.first);
    const auto rightChunks = getChunks(pair.second);
    return simplify(merge(leftChunks, rightChunks));
}
