#pragma once

#include <SFML/Window/Event.hpp>

#include "sfml_fwd.hpp"

void handle_key_pressed(const sf::Event &event,
                        SceneContext &scene,
                        AppState &state,
                        RuntimeUi &runtime_ui);

void handle_key_released(const sf::Event &event,
                         SceneContext &scene,
                         AppState &state,
                         RuntimeUi &runtime_ui);