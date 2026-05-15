#pragma once

#include <array>

constexpr std::size_t POSITION_SIZE = 10;
using Position = std::array<int, POSITION_SIZE>;

inline Position solved_position()
{
    return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
}
