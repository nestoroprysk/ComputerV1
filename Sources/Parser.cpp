#include "Parser.hpp"

#include <sstream>

namespace {

std::pair<std::string, std::string> splitAt(const std::string s, const char c)
{
    const auto i = std::find(s.cbegin(), s.cend(), c);
    return {std::string(s.cbegin(), i), std::string(std::next(i), s.cend())};
}

const std::string& validate(const std::string& s)
{
    // empty check
    if (s.empty())
        throw Parser::ParseError("Non-empty string expected");
    
    // allowed signs check
    {
    const auto allowedSigns = std::string(".+-Xx^*=");
    for (const auto ch : s)
        if (!std::isdigit(ch) && allowedSigns.find(ch) == std::string::npos)
            throw Parser::ParseError(std::string("Unrecognised symbol [") + ch + ']');
    }

    // = check
    {
        const auto n = std::count(s.cbegin(), s.cend(), '=');
        if (n != 1)
            throw Parser::ParseError("Expected single [=], got " + std::to_string(n));
    }

    return s;
}

std::string filterSpaces(const std::string& s)
{
    auto result = std::string();
    for (const auto c : s)
        if (!std::isspace(c))
            result += c;
    return result;
}

std::string toLower(const std::string& s)
{
    auto result = std::string();
    for (const auto ch : s)
        result += std::tolower(ch);
    return result;
}

template <typename T>
std::unique_ptr<T> get(std::stringstream& ss)
{
    if (!ss) return {};
    auto result = T();
    ss >> result;
    if (!ss.fail()) return std::make_unique<T>(result);
    return {};
}

bool get(std::stringstream& ss, const char ch)
{
    if (!ss) return {};
    auto result = char();
    ss >> result;
    return !ss.fail() && result == ch;
}

namespace ParserDetail {

// a: a * x ^ n
const auto a = [](std::stringstream ss) -> std::unique_ptr<Chunk>{
    const auto opt_coefficient = get<double>(ss);
    const auto opt_multiply = get(ss, '*');
    const auto opt_x = get(ss, 'x');
    const auto opt_power_sign = get(ss, '^');
    const auto opt_power = get<std::size_t>(ss);
    if (!opt_coefficient || !opt_multiply || !opt_x ||
        !opt_power_sign || !opt_power)
        return {};
    return std::make_unique<Chunk>(*opt_coefficient, *opt_power);
};

// b: a * x
const auto b = [](std::stringstream ss) -> std::unique_ptr<Chunk>{
    const auto opt_coefficient = get<double>(ss);
    const auto opt_multiply = get(ss, '*');
    const auto opt_x = get(ss, 'x');
    if (!opt_coefficient || !opt_multiply || !opt_x)
        return {};
    return std::make_unique<Chunk>(*opt_coefficient, 1);
};

// c: x ^ n
const auto c = [](std::stringstream ss) -> std::unique_ptr<Chunk>{
    const auto opt_x = get(ss, 'x');
    const auto opt_power_sign = get(ss, '^');
    const auto opt_power = get<std::size_t>(ss);
    if (!opt_x || !opt_power_sign || !opt_power)
        return {};
    return std::make_unique<Chunk>(1, *opt_power);
};

// d: axn
const auto d = [](std::stringstream ss) -> std::unique_ptr<Chunk>{
    const auto opt_coefficient = get<double>(ss);
    const auto opt_x = get(ss, 'x');
    const auto opt_power = get<std::size_t>(ss);
    if (!opt_coefficient || !opt_x || !opt_power)
        return {};
    return std::make_unique<Chunk>(*opt_coefficient, *opt_power);
};

// e: ax
const auto e = [](std::stringstream ss) -> std::unique_ptr<Chunk>{
    const auto opt_coefficient = get<double>(ss);
    const auto opt_x = get(ss, 'x');
    if (!opt_coefficient || !opt_x)
        return {};
    return std::make_unique<Chunk>(*opt_coefficient, 1);
};

// f: xn
const auto f = [](std::stringstream ss) -> std::unique_ptr<Chunk>{
    const auto opt_x = get(ss, 'x');
    const auto opt_power = get<std::size_t>(ss);
    if (!opt_x || !opt_power)
        return {};
    return std::make_unique<Chunk>(1, *opt_power);
};

// g: x
const auto g = [](std::stringstream ss) -> std::unique_ptr<Chunk>{
    const auto opt_x = get(ss, 'x');
    if (!opt_x)
        return {};
    return std::make_unique<Chunk>(1, 1);
};

// h: a
const auto h = [](std::stringstream ss) -> std::unique_ptr<Chunk>{
    const auto opt_coefficient = get<double>(ss);
    if (!opt_coefficient)
        return {};
    return std::make_unique<Chunk>(*opt_coefficient, 0);
};

}

// Possible forms:
// a: a * x ^ n
// b: a * x
// c: x ^ n
// d: axn
// e: ax
// f: xn
// g: x
// h: a
std::unique_ptr<Chunk> get(const std::string& s)
{
    using Parser = std::function<std::unique_ptr<Chunk>(std::stringstream)>;
    using namespace ParserDetail;
    static const auto ps = std::vector<Parser>{ a, b, c, d, e, f, g, h };
    for (const auto& p : ps)
        if (auto opt_chunk = p(std::stringstream(s)))
            return opt_chunk;
    return {}; 
}

std::vector<std::string> splitIncluding(const std::string& s, std::function<bool(char)> p)
{
    auto result = std::vector<std::string>();
    if (s.empty()) return {};
    if (!p(s[0])) result.emplace_back();
    for (const auto c : s){
        if (p(c)) result.emplace_back();
        result[result.size() - 1] += c;
    }
    return result;
}

std::vector<Chunk> getChunks(const std::string& s)
{
    auto result = std::vector<Chunk>();
    const auto ps = splitIncluding(s, [](const auto c){ return c == '+' || c == '-'; });
    for (const auto& p : ps){
        if (auto opt_chunk = get(p))
            result.emplace_back(std::move(*opt_chunk));
        else throw Parser::ParseError("Failed to parse [" + p + ']');
    }
    return result;
}

}

std::pair<std::vector<Chunk>, std::vector<Chunk>>
Parser::parse(const std::string& s)
{
    const auto pair = splitAt(toLower(validate(filterSpaces(s))), '=');
    return { getChunks(pair.first), getChunks(pair.second) };
}
