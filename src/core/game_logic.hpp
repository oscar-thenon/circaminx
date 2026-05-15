#pragma once

#include <array>

#include "position.hpp"
#include "move.hpp"

std::array<Move, 10> all_basic_moves();
void apply_move(Position &position, const Move &move);
void apply_move(Position &position, int move_code);
void initialize_position(Position &position);
bool is_solved(const Position &position);
bool is_solved_in_one_move(const Position &position);
void shuffle_position(Position &position);
void shuffle_final_positions(Position &position);
