#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>

#include "app_state.hpp"
#include "game_logic.hpp"
#include "game_loop.hpp"
#include "input_handlers.hpp"
#include "render_frame.hpp"
#include "runtime_ui.hpp"
#include "timer.hpp"
#include "scene_context.hpp"

namespace
{
void hide_values_if_needed(const AppState &state, SceneContext &scene, RuntimeUi &runtime_ui)
{
    if (!state.values_visible)
    {
        scene.move_counter_text.setString("");
        runtime_ui.timer_text.setString("");
        runtime_ui.score_text.setString("");
        return;
    }

    bool solved = is_solved(state.position);
    sf::Color text_color = solved ? scene.success_color : sf::Color::Black;
    runtime_ui.timer_text.setString(time_to_string(state.elapsed_seconds));
    runtime_ui.timer_text.setFillColor(text_color);
    double score = solved ? compute_score(state.elapsed_seconds, state.move_count) : 0.0;
    runtime_ui.score_text.setString(format_score(score));
    runtime_ui.score_text.setFillColor(text_color);
}

void process_events(SceneContext &scene, AppState &state, RuntimeUi &runtime_ui)
{
    sf::Event event;
    while (scene.window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            scene.window.close();
            break;

        case sf::Event::KeyPressed:
        {
            handle_key_pressed(event, scene, state, runtime_ui);
            break;
        }

        case sf::Event::KeyReleased:
            handle_key_released(event, scene, state, runtime_ui);
            break;

        default:
            break;
        }
    }
}
}

bool run_game_loop(SceneContext &scene, AppState &state, RuntimeUi &runtime_ui)
{
    while (scene.window.isOpen() && !state.fatal_error)
    {
        process_events(scene, state, runtime_ui);
        hide_values_if_needed(state, scene, runtime_ui);
        render_frame(scene, runtime_ui);
    }

    return !state.fatal_error;
}
