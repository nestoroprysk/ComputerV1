#pragma once

#include <cstddef>

struct Chunk
{
    explicit Chunk(const double i_c, const std::size_t i_p)
        : m_coefficient(i_c), m_power(i_p){}
    double m_coefficient = 0;
    std::size_t m_power = 0;
};
