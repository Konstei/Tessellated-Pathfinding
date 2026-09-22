#ifndef CORE_HPP
#define CORE_HPP

#include <cstdint>

std::uint32_t heuristic(std::uint32_t x1, std::uint32_t x2, std::uint32_t y1, std::uint32_t y2);

void astar_run(std::uint32_t rows, std::uint32_t cols, std::uint32_t sx, std::uint32_t sy);

#endif