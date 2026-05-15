#include <SFML/Window/Keyboard.hpp>

#include "app_state.hpp"
#include "game_logic.hpp"
#include "input_handlers.hpp"
#include "input_mapping.hpp"
#include "move_notation.hpp"
#include "position_io.hpp"
#include "runtime_ui.hpp"
#include "scene_context.hpp"
#include "timer.hpp"
#include "ui_render.hpp"
#include "util.hpp"

namespace
{
void reset_timer_and_score_local(RuntimeUi &runtime_ui, AppState &state)
{
    runtime_ui.clock.restart();
    runtime_ui.timer_text.setString("00:00.00");
    state.elapsed_seconds = 0.0;
    runtime_ui.score_text.setString("");
}

std::string puzzle_state_string(const Position &position)
{
    std::string state;
    state.reserve(10);
    for (int k = 0; k < 10; k++)
        state += std::to_string(position[k]);
    return state;
}

void apply_action(const Action &action,
                  sf::Keyboard::Key key,
                  SceneContext &scene,
                  AppState &state,
                  RuntimeUi &runtime_ui,
                  bool &has_action)
{
    std::string action_message;

    switch (action.kind)
    {
        case ActionKind::Quit:
            log_action("Window close requested");
            scene.window.close();
            return;

        case ActionKind::ToggleTimer:
            if (state.timer_running)
            {
                log_action("Timer stopped");
                stop_timer_and_reveal(runtime_ui, scene, state);
            }
            else
            {
                action_message = "Timer started";
                start_timer_and_hide(runtime_ui, state);
            }
            has_action = true;
            break;

        case ActionKind::Reset:
            initialize_position(state.position);
            state.move_count = 0;
            reset_timer_and_score_local(runtime_ui, state);
            has_action = true;
            action_message = "Position reset";
            break;

        case ActionKind::Shuffle:
            shuffle_position(state.position);
            copy_array_10(state.saved_position, state.position);
            state.move_count = 0;
            reset_timer_and_score_local(runtime_ui, state);
            has_action = true;
            action_message = std::string("Full position shuffle: ") + puzzle_state_string(state.position);
            break;

        case ActionKind::ResetMoveCounter:
            state.move_count = 0;
            has_action = true;
            action_message = "Move counter reset";
            break;

        case ActionKind::ToggleValues:
            if (!state.timer_running)
            {
                state.values_visible = !state.values_visible;
                has_action = true;
                action_message = state.values_visible ? "Values shown" : "Values hidden";
            }
            break;

        case ActionKind::Solve:
            initialize_position(state.position);
            has_action = true;
            action_message = "Position solved";
            break;

        case ActionKind::ShuffleFinalStep:
            shuffle_final_positions(state.position);
            state.move_count = 0;
            reset_timer_and_score_local(runtime_ui, state);
            has_action = true;
            action_message = std::string("Shuffled final position: ") + puzzle_state_string(state.position);
            break;

        case ActionKind::SavePosition:
            copy_array_10(state.saved_position, state.position);
            has_action = true;
            action_message = std::string("Current position saved: ") + puzzle_state_string(state.saved_position);
            break;

        case ActionKind::RestorePosition:
            copy_array_10(state.position, state.saved_position);
            has_action = true;
            action_message = std::string("Saved position restored: ") + puzzle_state_string(state.position);
            break;

        case ActionKind::ExportPosition:
            if (export_position("./export/position.txt", state.position))
            {
                has_action = true;
                action_message = std::string("Position exported: ") + puzzle_state_string(state.position);
            }
            else
            {
                state.fatal_error = true;
                log_action("Position export failed");
            }
            break;

        case ActionKind::TimesExportation:
            if (export_times())
                action_message = "Times exported";
            else
                action_message = "Times export failed";
            has_action = true;
            break;

        case ActionKind::ImportPosition:
            has_action = import_position("./export/position.txt", state.position);
            if (has_action)
                action_message = std::string("Position imported: ") + puzzle_state_string(state.position);
            else
                log_action("Position import failed");
            break;

        case ActionKind::ToggleRecording:
            if (!state.recording.is_recording)
            {
                state.recording.is_recording = true;
                state.recording.recorded_sequence.clear();
            }
            else
            {
                state.recording.is_recording = false;
                log_action(std::string("Recording sequence:\n> ") + state.recording.recorded_sequence);
            }
            break;

        case ActionKind::Move:
            apply_move(state.position, *action.move);
            state.move_count++;
            has_action = true;
            if (state.recording.is_recording)
            {
                std::string notation;
                if (move_to_human_notation(*action.move, notation))
                {
                    if (!state.recording.recorded_sequence.empty())
                        state.recording.recorded_sequence += ' ';
                    state.recording.recorded_sequence += notation;
                }
            }
            break;

        case ActionKind::None:
            break;
    }

    if (!action_message.empty())
        log_action(action_message);

    if (has_action)
        runtime_ui.click_sound.play();
}

void update_after_action(SceneContext &scene,
                         AppState &state,
                         RuntimeUi &runtime_ui,
                         bool has_action)
{
    if (state.fatal_error)
    {
        scene.window.close();
        return;
    }

    if (has_action)
    {
        update_display(state.position,
                       scene.symbol_sprites,
                       scene.texture_1,
                       scene.texture_1_rev,
                       scene.texture_2,
                       scene.texture_2_rev,
                       scene.texture_3,
                       scene.texture_3_rev,
                       scene.texture_4,
                       scene.texture_4_rev,
                       scene.texture_bottom,
                       scene.texture_top);
    }

    if (state.values_visible)
    {
        update_move_counter(scene.move_counter_text,
                            scene.screen_w_scale,
                            scene.screen_h_scale,
                            scene.success_color,
                            is_solved(state.position),
                            int_to_string(state.move_count));
    }
    else
    {
        scene.move_counter_text.setString("");
    }
}
}

// Handles keyboard input for the game.
// This function only converts input to Action and applies it.
void handle_key_pressed(const sf::Event &event,
                        SceneContext &scene,
                        AppState &state,
                        RuntimeUi &runtime_ui)
{
    bool has_action = false;

    sf::Keyboard::Key key = event.key.code;
    Action action = action_from_key(key);
    apply_action(action, key, scene, state, runtime_ui, has_action);
    update_after_action(scene, state, runtime_ui, has_action);
}

// Handles keyboard input for key releases.
// This function processes key releases and updates the game state accordingly.
void handle_key_released(const sf::Event &event,
                         SceneContext &scene,
                         AppState &state,
                         RuntimeUi &runtime_ui)
{
    (void)event;
    (void)scene;
    (void)state;
    (void)runtime_ui;
}
