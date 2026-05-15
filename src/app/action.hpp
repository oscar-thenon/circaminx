#pragma once

#include <optional>
#include "move.hpp"

enum class ActionKind
{
    None,
    Quit,
    Reset,
    Shuffle,
    ToggleTimer,
    ResetMoveCounter,
    ToggleValues,
    Solve,
    ShuffleFinalStep,
    SavePosition,
    RestorePosition,
    ExportPosition,
    TimesExportation,
    ImportPosition,
    ToggleRecording,
    Move
};

struct Action
{
    ActionKind          kind;
    std::optional<Move> move;
};
