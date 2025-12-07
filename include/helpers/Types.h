#pragma once
#include <string>
#include <vector>

struct Position {
    size_t x;
    size_t y;

    bool operator==(const Position& other) const {
        return this->x == other.x && this->y == other.y;
    }
};

struct PanelMetrics {
    size_t row, col, height, width;
};

struct Offset {
    int dx;
    int dy;
};

using MapTiles = std::vector<std::string>;

enum class Direction { UP, DOWN, LEFT, RIGHT };

constexpr Offset getOffsetFor(Direction dir) {
    switch (dir) {
    case Direction::UP:    return {0, -1};
    case Direction::DOWN:  return {0, 1};
    case Direction::LEFT:  return {-1, 0};
    case Direction::RIGHT: return {1, 0};
    default:               return {0, 0};
    }
}