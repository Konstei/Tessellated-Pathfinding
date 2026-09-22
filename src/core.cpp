#include "core.hpp"

#include <cmath>
#include <cfloat>
#include <memory>
#include <algorithm>
#include <queue>
#include <vector>
#include <mdspan>

#include "utils.hpp"


constexpr float SQRT_2 = 1.41421356f;



// Octile Heuristic
float heuristic(const std::uint32_t x1, const std::uint32_t y1, const std::uint32_t x2, const std::uint32_t y2)
{
    std::int64_t dx = std::abs(static_cast<std::int64_t>(x1) - static_cast<std::int64_t>(x2)),
                 dy = std::abs(static_cast<std::int64_t>(y1) - static_cast<std::int64_t>(y2));
    return (std::abs(dx - dy) + SQRT_2 * std::min(dx, dy));
}



std::vector<std::tuple<std::uint32_t, std::uint32_t>> astar_run (
    const std::mdspan<const bool, std::dextents<size_t, 2>> map,
    const std::uint32_t rows, const std::uint32_t cols,
    const std::uint32_t sx, const std::uint32_t sy,
    const std::uint32_t dx, const std::uint32_t dy
) {
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
        const float cost[8] = { SQRT_2, 1.0f, SQRT_2, 1.0f, 1.0f, SQRT_2, 1.0f, SQRT_2 };

        for (uint8_t i = 0; i < 8; i++)
        {
            std::int64_t tx = static_cast<std::int64_t>(cell.row) + dir_x[i],
                         ty = static_cast<std::int64_t>(cell.col) + dir_y[i];

            if (tx < 0 || ty < 0 || tx >= rows || ty >= cols || map[static_cast<size_t>(tx), static_cast<size_t>(ty)]) {    // I know the condition short-circuits in the case of the || operator finding a true before the map is accessed, but I reckon it's better to be sure (in case of strict compiler mode), since the conversion is done either way
                continue;
            }

            std::uint32_t ux = static_cast<std::uint32_t>(tx),
                          uy = static_cast<std::uint32_t>(ty);

            float g = g_score[cell.row, cell.col] + cost[i];

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
        std::vector<std::tuple<std::uint32_t, std::uint32_t>> path;
        std::uint32_t ux = dx, uy = dy;

        while (ux != sx || uy != sy)
        {
            path.push_back(std::make_tuple(ux, uy));

            switch (parents[ux, uy])
            {
                case -5:
                    ux++;
                    uy++;
                    break;
                
                case -3:
                    ux++;
                    break;
                
                case -1:
                    ux++;
                    uy--;
                    break;
                
                case -2:
                    uy++;
                    break;
                
                case 2:
                    uy--;
                    break;
                
                case 1:
                    ux--;
                    uy++;
                    break;
                
                case 3:
                    ux--;
                    break;
                
                case 5:
                    ux--;
                    uy--;
                    break;
                
                default:
                    break;
            }
        }

        path.push_back(std::make_tuple(sx, sy));

        return path;
    }
}
