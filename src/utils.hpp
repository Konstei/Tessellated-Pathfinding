#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>

struct Cell
{
    std::uint32_t row, col;
    float dist;

    static Cell create(std::uint32_t r, std::uint32_t c, float dist);

    bool operator<(const Cell& other) const;
    bool operator>(const Cell& other) const;
};

#endif