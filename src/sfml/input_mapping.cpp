#include "input_mapping.hpp"

#include <unordered_map>

std::optional<Move> key_to_move(sf::Keyboard::Key key)
{
    static const std::unordered_map<sf::Keyboard::Key, Move> key_map = {
        {sf::Keyboard::Q, {Circle::Left,  Rotation::CounterClockwise, 2}},
        {sf::Keyboard::S, {Circle::Left,  Rotation::CounterClockwise, 1}},
        {sf::Keyboard::D, {Circle::Left,  Rotation::Clockwise,        3}},
        {sf::Keyboard::F, {Circle::Left,  Rotation::Clockwise,        1}},
        {sf::Keyboard::G, {Circle::Left,  Rotation::Clockwise,        2}},
        {sf::Keyboard::H, {Circle::Right, Rotation::CounterClockwise, 2}},
        {sf::Keyboard::J, {Circle::Right, Rotation::CounterClockwise, 1}},
        {sf::Keyboard::K, {Circle::Right, Rotation::Clockwise,        3}},
        {sf::Keyboard::L, {Circle::Right, Rotation::Clockwise,        1}},
        {sf::Keyboard::M, {Circle::Right, Rotation::Clockwise,        2}},
    };
    auto it = key_map.find(key);
    if (it != key_map.end())
        return it->second;
    return std::nullopt;
}

Action action_from_key(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Escape:   return {ActionKind::Quit,             std::nullopt};
    case sf::Keyboard::Space:    return {ActionKind::ToggleTimer,      std::nullopt};
    case sf::Keyboard::Num0:     return {ActionKind::Reset,            std::nullopt};
    case sf::Keyboard::Multiply: return {ActionKind::Shuffle,          std::nullopt};
    case sf::Keyboard::Delete:   return {ActionKind::ResetMoveCounter, std::nullopt};
    case sf::Keyboard::Tab:      return {ActionKind::ToggleValues,     std::nullopt};
    case sf::Keyboard::Home:     return {ActionKind::Solve,            std::nullopt};
    case sf::Keyboard::C:        return {ActionKind::ShuffleFinalStep, std::nullopt};
    case sf::Keyboard::Return:   return {ActionKind::SavePosition,     std::nullopt};
    case sf::Keyboard::Z:        return {ActionKind::RestorePosition,  std::nullopt};
    case sf::Keyboard::E:        return {ActionKind::ExportPosition,   std::nullopt};
    case sf::Keyboard::T:        return {ActionKind::TimesExportation, std::nullopt};
    case sf::Keyboard::I:        return {ActionKind::ImportPosition,   std::nullopt};
    case sf::Keyboard::R:        return {ActionKind::ToggleRecording,  std::nullopt};
    default:
        break;
    }
    std::optional<Move> move = key_to_move(key);
    if (move)
        return {ActionKind::Move, move};
    return {ActionKind::None, std::nullopt};
}
