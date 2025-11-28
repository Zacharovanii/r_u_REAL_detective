#include "ui/MapRenderer.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include <iostream>

static std::string colorOf(char tile) {
    switch (tile) {
    case '.': return "\033[38;5;242m";  // земля
    case ',': return "\033[38;5;34m";   // трава
    case '~': return "\033[38;5;31m";   // вода
    case '#': return "\033[38;5;250m";  // стена
    case 'N': return "\033[1;33m";      // npc
    case 'I': return "\033[1;36m";      // item
    default:  return "\033[0m";
    }
}

void MapRenderer::draw(const Model& model, int row, int col, int radius) {
    int diameter = radius * 2 + 1;

    int frameHeight = diameter + 2;
    int frameWidth  = diameter + 2;

    FrameDrawer::drawFrame(row, col, frameHeight, frameWidth);

    drawAreaAroundPlayer(model, row + 1, col + 1, radius);
}

void MapRenderer::drawAreaAroundPlayer(const Model& model, int row, int col, int radius) {
    const auto& map = model.getMap();
    const auto& p   = model.getPlayer();

    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {

            int y = p.y + dy;
            int x = p.x + dx;

            TerminalUtils::moveCursor(row + (dy + radius), col + (dx + radius));

            if (y < 0 || x < 0 || y >= map.size() || x >= map[0].size()) {
                std::cout << " ";
                continue;
            }

            if (y == p.y && x == p.x) {
                std::cout << "\033[1;32m@\033[0m";
                continue;
            }

            char tile = map[y][x];
            std::cout << colorOf(tile) << tile << "\033[0m";
        }
    }
}
