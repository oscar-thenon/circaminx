#pragma once

#include <string>

#include "move.hpp"

inline bool move_to_human_notation(const Move &move, std::string &notation)
{
    if (move.circle == Circle::Left)
    {
        if (move.rotation == Rotation::CounterClockwise && move.steps == 2) { notation = "L--"; return true; }
        if (move.rotation == Rotation::CounterClockwise && move.steps == 1) { notation = "L-"; return true; }
        if (move.rotation == Rotation::Clockwise && move.steps == 3) { notation = "L3"; return true; }
        if (move.rotation == Rotation::Clockwise && move.steps == 1) { notation = "L+"; return true; }
        if (move.rotation == Rotation::Clockwise && move.steps == 2) { notation = "L++"; return true; }
    }
    else
    {
        if (move.rotation == Rotation::CounterClockwise && move.steps == 2) { notation = "R--"; return true; }
        if (move.rotation == Rotation::CounterClockwise && move.steps == 1) { notation = "R-"; return true; }
        if (move.rotation == Rotation::Clockwise && move.steps == 3) { notation = "R3"; return true; }
        if (move.rotation == Rotation::Clockwise && move.steps == 1) { notation = "R+"; return true; }
        if (move.rotation == Rotation::Clockwise && move.steps == 2) { notation = "R++"; return true; }
    }

    return false;
}
