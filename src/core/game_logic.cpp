#include <algorithm>

#include "game_logic.hpp"
#include "position.hpp"
#include "util.hpp"

// Rotates the left part of the position counter-clockwise (indices 0 to 5).
static void rotate_left_ccw(Position &position)
{
    std::rotate(position.begin(), position.begin() + 5, position.begin() + 6);
}
// Rotates the left part of the position clockwise (indices 0 to 5).
static void rotate_left_cw(Position &position)
{
    std::rotate(position.begin(), position.begin() + 1, position.begin() + 6);
}
// Rotates the right part of the position counter-clockwise (indices 4 to 9).
static void rotate_right_ccw(Position &position)
{
    std::rotate(position.begin() + 4, position.begin() + 5, position.end());
}
// Rotates the right part of the position clockwise (indices 4 to 9).
static void rotate_right_cw(Position &position)
{
    std::rotate(position.begin() + 4, position.begin() + 9, position.end());
}

// Applies a single step rotation to the position.
static void apply_step(Position &position, Circle circle, Rotation rotation)
{
    if (circle == Circle::Left && rotation == Rotation::CounterClockwise)
        rotate_left_ccw(position);
    else if (circle == Circle::Left && rotation == Rotation::Clockwise)
        rotate_left_cw(position);
    else if (circle == Circle::Right && rotation == Rotation::CounterClockwise)
        rotate_right_ccw(position);
    else
        rotate_right_cw(position);
}

// Applies a Move (typed) to the position.
void apply_move(Position &position, const Move &move)
{
    for (int i = 0; i < move.steps; ++i)
        apply_step(position, move.circle, move.rotation);
}

// Decodes a move character to a Move struct.
static Move char_to_move(int move_code)
{
    switch (move_code)
    {
    case 'q': return {Circle::Left,  Rotation::CounterClockwise, 2};
    case 's': return {Circle::Left,  Rotation::CounterClockwise, 1};
    case 'd': return {Circle::Left,  Rotation::Clockwise,        3};
    case 'f': return {Circle::Left,  Rotation::Clockwise,        1};
    case 'g': return {Circle::Left,  Rotation::Clockwise,        2};
    case 'h': return {Circle::Right, Rotation::CounterClockwise, 2};
    case 'j': return {Circle::Right, Rotation::CounterClockwise, 1};
    case 'k': return {Circle::Right, Rotation::Clockwise,        3};
    case 'l': return {Circle::Right, Rotation::Clockwise,        1};
    case 'm': return {Circle::Right, Rotation::Clockwise,        2};
    default:  return {Circle::Left,  Rotation::Clockwise,        0};
    }
}

// Compatibility shim: applies a move to the position based on the given move code.
void apply_move(Position &position, int move_code)
{
    apply_move(position, char_to_move(move_code));
}

// Initializes the position array to its default state (0 to 9).
void initialize_position(Position &position)
{
    position = solved_position();
}

// Checks if the position is solved (all elements in order).
bool is_solved(const Position &position)
{
    return position == solved_position();
}

std::array<Move, 10> all_basic_moves()
{
    return {{
        {Circle::Left,  Rotation::CounterClockwise, 1},
        {Circle::Left,  Rotation::CounterClockwise, 2},
        {Circle::Left,  Rotation::Clockwise,        1},
        {Circle::Left,  Rotation::Clockwise,        2},
        {Circle::Left,  Rotation::Clockwise,        3},
        {Circle::Right, Rotation::CounterClockwise, 1},
        {Circle::Right, Rotation::CounterClockwise, 2},
        {Circle::Right, Rotation::Clockwise,        1},
        {Circle::Right, Rotation::Clockwise,        2},
        {Circle::Right, Rotation::Clockwise,        3},
    }};
}

// Checks if the position can be solved in one move.
bool is_solved_in_one_move(const Position &position)
{
    for (Move move : all_basic_moves())
    {
        Position copy = position;
        apply_move(copy, move);
        if (is_solved(copy))
        {
            return true;
        }
    }
    return false;
}

// Shuffles the position array until it is not solved or solvable in one move.
void shuffle_position(Position &position)
{
	do
	{
		shuffle_int_array(position.data(), 10);
	} while (is_solved(position) or is_solved_in_one_move(position));
}

void shuffle_final_positions(Position &position)
{
    int final_set[4] = {3, 4, 5, 9};
    position = solved_position();
    do
    {
        shuffle_int_array(final_set, 4);
        position[3] = final_set[0];
        position[4] = final_set[1];
        position[5] = final_set[2];
        position[9] = final_set[3];
    } while (is_solved(position));
}