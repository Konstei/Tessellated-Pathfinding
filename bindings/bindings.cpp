#include <emscripten/bind.h>
#include <cstdint>
#include <tuple>
#include <vector>
#include "../src/core.hpp"

using PointTuple = std::tuple<std::uint32_t, std::uint32_t>;

EMSCRIPTEN_BINDINGS(astar) {
    emscripten::value_array<PointTuple>("PointTuple")
        .element(
            +[](const PointTuple& t) -> std::uint32_t { return std::get<0>(t); },
            +[](PointTuple& t, std::uint32_t val) { std::get<0>(t) = val; }
        )
        .element(
            +[](const PointTuple& t) -> std::uint32_t { return std::get<1>(t); },
            +[](PointTuple& t, std::uint32_t val) { std::get<1>(t) = val; }
        );

    emscripten::register_vector<PointTuple>("PointVector");

    emscripten::function("astarRun", &astar_run);
}
