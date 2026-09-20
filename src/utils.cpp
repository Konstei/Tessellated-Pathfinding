#include "utils.hpp"

Cell Cell::create(unsigned int r, unsigned int c, float dist)
{
    return Cell{r, c, dist};
}