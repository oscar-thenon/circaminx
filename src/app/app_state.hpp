#pragma once
#include "position.hpp"

#include <string>

struct RecordingState
{
    bool is_recording = false;
    std::string recorded_sequence;
};

struct AppState
{
    Position position = solved_position();
    Position saved_position = solved_position();
    int move_count;

    bool timer_running;
    bool values_visible;
    bool fatal_error;

    double elapsed_seconds = 0.0;
    RecordingState recording;
};
