#pragma once

enum class Circle
{
    Left,
    Right
};

enum class Rotation
{
    Clockwise,
    CounterClockwise
};

struct Move
{
    Circle   circle;
    Rotation rotation;
    int      steps;
};
