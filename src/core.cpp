#include "core.hpp"

#include <cmath>
#include <algorithm>
#include <mdspan>
#include <queue>
#include <memory>
#include <cfloat>

#include "utils.hpp"

#define SQRT_2 1.414
#define MIN_COST 1


// Octile Heuristic
std::uint32_t heuristic(std::uint32_t x1, std::uint32_t y1, std::uint32_t x2, std::uint32_t y2)
{
    std::int64_t dx = std::abs(static_cast<std::int64_t>(x1) - static_cast<std::int64_t>(x2)),
                 dy = std::abs(static_cast<std::int64_t>(y1) - static_cast<std::int64_t>(y2));
    return static_cast<std::uint32_t>(std::abs(dx - dy) + SQRT_2 * std::min(dx, dy));
}



void astar_run(/* flattened map, */ std::uint32_t rows, std::uint32_t cols, std::uint32_t sx, std::uint32_t sy, std::uint32_t dx, std::uint32_t dy)
{
    auto g_score_ = std::make_unique<float[]>(rows * cols);
    auto visited_ = std::make_unique<bool[]>(rows * cols);
    auto parents_ = std::make_unique<int8_t[]>(rows * cols);

    std::fill_n(g_score_.get(), rows * cols, FLT_MAX);
    std::fill_n(visited_.get(), rows * cols, false);

    std::mdspan<float, std::dextents<size_t, 2>> g_score(g_score_.get(), rows, cols);
    std::mdspan<bool, std::dextents<size_t, 2>> visited(visited_.get(), rows, cols);
    std::mdspan<int8_t, std::dextents<size_t, 2>> parents(parents_.get(), rows, cols);

    g_score[sx, sy] = 0;

    std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> pqueue;
    pqueue.push(Cell::create(sx, sy, heuristic(sx, sy, dx, dy)));

    bool found = false;

    while (!pqueue.empty())
    {
        Cell cell = pqueue.top();
        pqueue.pop();

        if (visited[cell.row, cell.col]) {
            continue;
        }
        visited[cell.row, cell.col] = true;

        if (cell.row == dx && cell.col == dy) {
            found = true;
            break;
        }

        // expand
        const int8_t dir_x[] = {-1, -1, -1,  0, 0,  1, 1, 1};
        const int8_t dir_y[] = {-1,  0,  1, -1, 1, -1, 0, 1};

        for (uint8_t i = 0; i < 8; i++)
        {
            std::int64_t tx = static_cast<std::int64_t>(cell.row) + dir_x[i],
                         ty = static_cast<std::int64_t>(cell.col) + dir_y[i];

            if (tx < 0 || ty < 0 || tx >= rows || ty >= cols /*    ||    harta[x][y] */) {
                continue;
            }

            std::uint32_t ux = static_cast<std::uint32_t>(tx),
                          uy = static_cast<std::uint32_t>(ty);

            float g = g_score[cell.row, cell.col];
            switch (!!dir_x[i] + !!dir_y[i])
            {
                case 1:
                    g += 1;
                    break;

                case 2:
                    g += SQRT_2;
                    break;
                
                default:
                    break;
            }

            if (g < g_score[ux, uy]) {
                g_score[ux, uy] = g;
                parents[ux, uy] = 3 * dir_x[i] + 2 * dir_y[i];

                pqueue.push(Cell::create(
                    ux,
                    uy,
                    g + heuristic(ux, uy, dx, dy)
                ));
            }

        }
    }

    if (found) {
        // reconstruct
    }
}
