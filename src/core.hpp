#ifndef CORE_HPP
#define CORE_HPP

#include <cstdint>
#include <vector>
#include <mdspan>

float heuristic(const std::uint32_t x1, const std::uint32_t x2, const std::uint32_t y1, const std::uint32_t y2);

std::vector<std::tuple<std::uint32_t, std::uint32_t>> astar_run (
    const std::mdspan<const bool, std::dextents<size_t, 2>> map,
    const std::uint32_t rows, const std::uint32_t cols,
    const std::uint32_t sx, const std::uint32_t sy,
    const std::uint32_t dx, const std::uint32_t dy
);

#endif
