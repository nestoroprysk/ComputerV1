#include "Simplifier.hpp"
#include "Utils.hpp"

#include <unordered_map>

namespace {

using Power = std::size_t;
struct Coefficient { double m_coefficient = 0; };

std::vector<Chunk> copyNonZero(const std::unordered_map<Power, Coefficient>& i_input)
{
    auto result = std::vector<Chunk>();
    for (const auto& pair : i_input)
        if (!Utils::eq(pair.second.m_coefficient, 0))
            result.emplace_back(pair.second.m_coefficient, pair.first);
    return result;
}

std::vector<Chunk> sort(std::vector<Chunk> io_v)
{
    std::sort(io_v.begin(), io_v.end(),
        [](const auto& lhs, const auto& rhs)
            { return lhs.m_power < rhs.m_power; });
    return io_v;
}

}

std::vector<Chunk>
Simplifier::simplify(const std::pair<std::vector<Chunk>,
    std::vector<Chunk>>& i_input)
{
    auto hash = std::unordered_map<Power, Coefficient>();
    for (const auto& c : i_input.first)
        hash[c.m_power].m_coefficient += c.m_coefficient;
    for (const auto& c : i_input.second)
        hash[c.m_power].m_coefficient -= c.m_coefficient;
    return sort(copyNonZero(hash));
}
