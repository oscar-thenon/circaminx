#include "runtime_ui.hpp"

#include "app_state.hpp"
#include "game_logic.hpp"
#include "timer.hpp"
#include "scene_context.hpp"

bool initialize_runtime_ui(RuntimeUi &runtime_ui, const SceneContext &scene)
{
    if (!runtime_ui.click_buffer.loadFromFile("./assets/sounds/click.ogg"))
        return false;
    runtime_ui.click_sound.setBuffer(runtime_ui.click_buffer);
    runtime_ui.timer_text.setFont(scene.main_font);
    runtime_ui.timer_text.setFillColor(sf::Color::Black);
    runtime_ui.timer_text.setCharacterSize(60 * scene.screen_h_scale);
    runtime_ui.timer_text.setPosition(scene.screen_w_scale * 37, scene.screen_h_scale * 21);
    runtime_ui.timer_text.setString("00:00.00");
    runtime_ui.score_text.setFont(scene.main_font);
    runtime_ui.score_text.setFillColor(sf::Color::Black);
    runtime_ui.score_text.setCharacterSize(50 * scene.screen_h_scale);
    runtime_ui.score_text.setPosition(scene.screen_w_scale * 37, scene.screen_h_scale * 999);
    runtime_ui.score_text.setString("");

    return true;
}

void update_timer_and_score(RuntimeUi &runtime_ui, const SceneContext &scene, const AppState &state)
{
    bool solved = is_solved(state.position);
    sf::Color text_color = solved ? scene.success_color : sf::Color::Black;
    runtime_ui.timer_text.setString(time_to_string(state.elapsed_seconds));
    runtime_ui.timer_text.setFillColor(text_color);
    double score = solved ? compute_score(state.elapsed_seconds, state.move_count) : 0.0;
    runtime_ui.score_text.setString(format_score(score));
    runtime_ui.score_text.setFillColor(text_color);
}

void start_timer_and_hide(RuntimeUi &runtime_ui, AppState &state)
{
    runtime_ui.clock.restart();
    runtime_ui.timer_text.setString("");
    runtime_ui.score_text.setString("");
    state.timer_running = true;
    state.values_visible = false;
}

void stop_timer_and_reveal(RuntimeUi &runtime_ui, const SceneContext &scene, AppState &state)
{
    state.elapsed_seconds = runtime_ui.clock.getElapsedTime().asMilliseconds() / 1000.0;

    int status = 0;
    if (is_solved(state.position))
        status = 1;
    else if (is_solved_in_one_move(state.position))
        status = 2;
    register_time_sample(state.elapsed_seconds, state.move_count, status);
    print_time();

    update_timer_and_score(runtime_ui, scene, state);
    state.timer_running = false;
    state.values_visible = true;
}
