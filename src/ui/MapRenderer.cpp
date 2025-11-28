#include "ui/MapRenderer.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include <iostream>

static constexpr std::string_view colorOf(char tile) {
    switch (tile) {
        case '.': return "\033[38;5;242m";
        case ',': return "\033[38;5;34m";
        case '~': return "\033[38;5;31m";
        case '#': return "\033[38;5;250m";
        case 'N': return "\033[1;33m";
        case 'I': return "\033[1;36m";
        default:  return "\033[0m";
    }
}

MapRenderer::MapRenderer(const Model& model) : model(model) { }

void MapRenderer::draw(int row, int col, int radiusY, int radiusX) const {
    int height = radiusY * 2 + 1;
    int width  = radiusX * 2 + 1;

    FrameDrawer::drawFrame(row, col, height + 2, width + 2);
    drawAreaAroundPlayer(row + 1, col + 1, radiusY, radiusX);
}

void MapRenderer::draw(int row, int col, int radius) const {
    draw(row, col, radius, radius);
}

void MapRenderer::drawAreaAroundPlayer(int row, int col,
                                      int radiusY, int radiusX) const {
    for (int dy = -radiusY; dy <= radiusY; dy++) {
        for (int dx = -radiusX; dx <= radiusX; dx++) {
            drawTile(row, col, radiusY, radiusX, dy, dx);
        }
    }
}

void MapRenderer::drawTile(int row,     int col,
                           int radiusY, int radiusX,
                           int dy,      int dx) const {
    const auto& map = model.getMap();
    const auto& p   = model.getPlayer();

    int checkY = static_cast<int>(p.y) + dy;
    int checkX = static_cast<int>(p.x) + dx;

    TerminalUtils::moveCursor(row + (dy + radiusY), col + (dx + radiusX));

    if (!isValidPosition(checkY, checkX)) {
        std::cout << " ";
        return;
    }

    auto y = static_cast<size_t>(checkY);
    auto x = static_cast<size_t>(checkX);

    if (y == p.y && x == p.x) {
        std::cout << "\033[1;32m@\033[0m";
        return;
    }

    std::cout << colorOf(map[y][x]) << map[y][x] << "\033[0m";
}

bool MapRenderer::isValidPosition(int y, int x) const {
    return y >= 0 && x >= 0 &&
           y < static_cast<int>(model.getMapSizeY()) &&
           x < static_cast<int>(model.getMapSizeX(static_cast<size_t>(y)));
}