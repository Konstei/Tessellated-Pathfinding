#ifndef UTILS_HPP
#define UTILS_HPP

struct Cell
{
    unsigned int r, c;
    float dist;

    static Cell create(unsigned int r, unsigned int c, float dist);
};

#endif