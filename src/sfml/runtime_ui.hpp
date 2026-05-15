#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

#include "sfml_fwd.hpp"

struct RuntimeUi
{
    sf::SoundBuffer click_buffer;
    sf::Sound click_sound;
    sf::Clock clock;
    sf::Text timer_text;
    sf::Text score_text;
};

bool initialize_runtime_ui(RuntimeUi &runtime_ui, const SceneContext &scene);
void update_timer_and_score(RuntimeUi &runtime_ui, const SceneContext &scene, const AppState &state);
void start_timer_and_hide(RuntimeUi &runtime_ui, AppState &state);
void stop_timer_and_reveal(RuntimeUi &runtime_ui, const SceneContext &scene, AppState &state);
