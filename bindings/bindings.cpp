#include <emscripten/bind.h>

#include "core.hpp"

EMSCRIPTEN_BINDINGS(astar) {
    emscripten::function("astarRun", &astar_run);
}
