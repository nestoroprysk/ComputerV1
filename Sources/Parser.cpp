#include "Parser.hpp"
#include "Utils.hpp"

#include <optional>

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

std::string::const_iterator findSizeTEnd(const std::string& s)
{
    auto result = s.cbegin();
    if (s.empty()) return result;
    while (result != s.cend() && std::isdigit(*result))
        ++result;
    return result;
}

std::optional<std::size_t> getSizeT(std::string& s)
{
    const auto end = findSizeTEnd(s);
    const auto sizeTCandidate = std::string(s.cbegin(), end);
    try{
        const auto result = std::stoull(sizeTCandidate);
        s = std::string(end, s.cend());
        return result;
    }
    catch (...){
        return {};
    }
}

std::string::const_iterator findDoubleEnd(const std::string& s)
{
    auto result = s.cbegin();
    if (s.empty()) return result;
    if (*result == '+' || *result == '-')
        ++result;
    auto dotMet = false;
    while (true){
        if (result == s.cend())
            break;
        if (std::isdigit(*result)){
            ++result;
            continue;
        }
        if (*result == '.' && !dotMet){
            ++result;
            dotMet = true;
            continue;
        }
        return result;
    }
    return result;
}

std::optional<double> getDouble(std::string& s)
{
    const auto end = findDoubleEnd(s);
    const auto doubleCandidate = std::string(s.cbegin(), end);
    try{
        const auto result = std::stod(doubleCandidate);
        s = std::string(end, s.cend());
        return result;
    }
    catch (...){
        return {};
    }
}

bool get(std::string& s, const char ch)
{
    if (s.empty()) return {};
    const auto result = s[0] == ch;
    if (result)
        s = std::string(std::next(s.cbegin()), s.cend());
    return result;
}

namespace ParserDetail {

// a: a * x ^ n
const auto a = [](std::string s) -> std::optional<Chunk>{
    const auto opt_coefficient = getDouble(s);
    const auto opt_multiply = get(s, '*');
    const auto opt_x = get(s, 'x');
    const auto opt_power_sign = get(s, '^');
    const auto opt_power = getSizeT(s);
    if (!s.empty() || !opt_coefficient || !opt_multiply || !opt_x ||
        !opt_power_sign || !opt_power)
        return {};
    return std::make_optional<Chunk>(*opt_coefficient, *opt_power);
};

// b: a * x
const auto b = [](std::string s) -> std::optional<Chunk>{
    const auto opt_coefficient = getDouble(s);
    const auto opt_multiply = get(s, '*');
    const auto opt_x = get(s, 'x');
    if (!s.empty() || !opt_coefficient || !opt_multiply || !opt_x)
        return {};
    return std::make_optional<Chunk>( *opt_coefficient, 1 );
};

// c: ax^n
const auto c = [](std::string s) -> std::optional<Chunk>{
    const auto opt_coefficient = getDouble(s);
    const auto opt_x = get(s, 'x');
    const auto opt_power_sign = get(s, '^');
    const auto opt_power = getSizeT(s);
    if (!s.empty() || !opt_coefficient || !opt_x || !opt_power_sign || !opt_power)
        return {};
    return std::make_optional<Chunk>( *opt_coefficient, *opt_power );
};

// d: x ^ n
const auto d = [](std::string s) -> std::optional<Chunk>{
    [[maybe_unused]] const auto opt_plus = get(s, '+');
    const auto opt_minus = get(s,'-');
    const auto opt_x = get(s, 'x');
    const auto opt_power_sign = get(s, '^');
    const auto opt_power = getSizeT(s);
    if (!s.empty() || !opt_x || !opt_power_sign || !opt_power)
        return {};
    return std::make_optional<Chunk>(static_cast<double>(opt_minus ? -1 : 1), *opt_power);
};

// e: axn
const auto e = [](std::string s) -> std::optional<Chunk>{
    const auto opt_coefficient = getDouble(s);
    const auto opt_x = get(s, 'x');
    const auto opt_power = getSizeT(s);
    if (!s.empty() || !opt_coefficient || !opt_x || !opt_power)
        return {};
    return std::make_optional<Chunk>(*opt_coefficient, *opt_power);
};

// f: ax
const auto f = [](std::string s) -> std::optional<Chunk>{
    const auto opt_coefficient = getDouble(s);
    const auto opt_x = get(s, 'x');
    if (!s.empty() || !opt_coefficient || !opt_x)
        return {};
    return std::make_optional<Chunk>(*opt_coefficient, 1);
};

// g: xn
const auto g = [](std::string s) -> std::optional<Chunk>{
    [[maybe_unused]] const auto opt_plus = get(s, '+');
    const auto opt_minus = get(s,'-');
    const auto opt_x = get(s, 'x');
    const auto opt_power = getSizeT(s);
    if (!s.empty() || !opt_x || !opt_power)
        return {};
    return std::make_optional<Chunk>(static_cast<double>(opt_minus ? -1 : 1), *opt_power);
};

// h: x
const auto h = [](std::string s) -> std::optional<Chunk>{
    [[maybe_unused]] const auto opt_plus = get(s, '+');
    const auto opt_minus = get(s,'-');
    const auto opt_x = get(s, 'x');
    if (!s.empty() || !opt_x)
        return {};
    return std::make_optional<Chunk>(static_cast<double>(opt_minus ? -1 : 1), 1);
};

// i: a
const auto i = [](std::string s) -> std::optional<Chunk>{
    const auto opt_coefficient = getDouble(s);
    if (!s.empty() || !opt_coefficient)
        return {};
    return std::make_optional<Chunk>(*opt_coefficient, 0);
};

}

std::optional<Chunk> get(const std::string& s)
{
    using Parser = std::function<std::optional<Chunk>(std::string)>;
    using namespace ParserDetail;
    static const auto ps = std::vector<Parser>{ a, b, c, d, e, f, g, h, i };
    for (const auto& p : ps)
        if (auto opt_chunk = p(s))
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
    auto lhs = getChunks(pair.first);
    if (lhs.empty()) throw Parser::ParseError("Non-empty lhs expected");
    auto rhs = getChunks(pair.second);
    if (rhs.empty()) throw Parser::ParseError("Non-empty rhs expected");
    return { std::move(lhs), std::move(rhs) };
}
