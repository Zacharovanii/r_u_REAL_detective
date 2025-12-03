#pragma once
#include <utility>
#include <string>
#include <vector>
#include <cstddef>

using Position = std::pair<size_t, size_t>;
using pos_diff = std::pair<ptrdiff_t, ptrdiff_t>;
using MapTiles = std::vector<std::string>;

enum class Direction { UP, DOWN, LEFT, RIGHT };

constexpr pos_diff offset(Direction dir) {
    switch (dir) {
    case Direction::UP:    return {0, -1};
    case Direction::DOWN:  return {0, 1};
    case Direction::LEFT:  return {-1, 0};
    case Direction::RIGHT: return {1, 0};
    default:               return {0, 0};
    }
}