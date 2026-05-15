#pragma once
#include <string>
#include "position.hpp"

int random_int(int a, int b);
void shuffle_int_array(int *values, int size);
std::string int_to_string(int n);
void copy_array_10(Position &dest, const Position &src);
int char_to_int(char c);
std::string current_datetime_string();
void log_action(const std::string &message_action);