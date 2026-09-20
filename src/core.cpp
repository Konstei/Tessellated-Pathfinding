#include "core.hpp"

#include <cmath>
#include <algorithm>
#include <mdspan>
#include <queue>
#include <memory>
#include <cfloat>

#include "utils.hpp"

#define SQRT2 1.414
#define MIN_COST 1


// Octile Heuristic
unsigned int heuristic(int x1, int x2, int y1, int y2)
{
    int dx = std::abs(x1 - x2), dy = std::abs(y1 - y2);
    return (std::abs(dx - dy) + SQRT2 * std::min(dx, dy));
}



void astar_run(unsigned int rows, unsigned int cols, unsigned int sx, unsigned int sy)
{
    auto g_score_ = std::make_unique<float[]>(rows * cols);
    auto visited_ = std::make_unique<bool[]>(rows * cols);
    auto parent_ = std::make_unique<uint8_t[]>(rows * cols);

    std::fill_n(g_score_.get(), rows * cols, FLT_MAX);
    std::fill_n(visited_.get(), rows * cols, 0);

    std::mdspan<float, std::dextents<size_t, 2>> g_score(g_score_.get(), rows, cols);
    std::mdspan<bool, std::dextents<size_t, 2>> visited(visited_.get(), rows, cols);
    std::mdspan<uint8_t, std::dextents<size_t, 2>> parent(parent_.get(), rows, cols);

    g_score[sx, sy] = 0;

    std::priority_queue<Cell> pqueue;
    // pqueue.

}
