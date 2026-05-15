#pragma once

#include <string>
#include "position.hpp"

bool import_position(const std::string &file_name, Position &position);
bool export_position(const std::string &file_name, const Position &position);
