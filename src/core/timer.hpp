#pragma once

#include <array>
#include <string>
#include <vector>

using ScoreTimeRow = std::array<double, 6>;

std::string time_to_string(double elapsed_seconds);
double compute_score(double elapsed_seconds, int move_count);
std::string format_score(double score);
void register_time_sample(double elapsed_seconds, int move_count, int status);
void print_time();
bool export_times();
const std::vector<ScoreTimeRow> &times_table();