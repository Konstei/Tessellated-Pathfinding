#include "utils.hpp"

Cell Cell::create(std::uint32_t r, std::uint32_t c, float dist)
{
    return Cell{r, c, dist};
}

bool Cell::operator<(const Cell &other) const
{
    return (this->dist < other.dist);
}

bool Cell::operator>(const Cell &other) const
{
    return (this->dist > other.dist);
}
