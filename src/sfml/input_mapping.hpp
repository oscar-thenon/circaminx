#pragma once

#include <optional>
#include <SFML/Window/Keyboard.hpp>

#include "move.hpp"
#include "action.hpp"

std::optional<Move> key_to_move(sf::Keyboard::Key key);
Action action_from_key(sf::Keyboard::Key key);
