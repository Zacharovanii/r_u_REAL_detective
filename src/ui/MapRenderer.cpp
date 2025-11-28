#include "ui/MapRenderer.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include <iostream>

static std::string colorOf(char tile) {
    switch (tile) {
    case '.': return "\033[0;32m";  // трава
    case ',': return "\033[1;32m";  // высокая трава
    case '~': return "\033[36m";    // вода
    case '#': return "\033[37m";    // камень/дом
    case 'N': return "\033[1;33m";  // npc
    case 'I': return "\033[1;36m";  // item
    default:  return "\033[0m";
    }
}

void MapRenderer::draw(const Model& model, int row, int col) {
    const auto& map = model.getMap();
    const auto& p   = model.getPlayer();

    int panelHeight = 11;
    int panelWidth  = 20;

    FrameDrawer::drawFrame(row, col, panelHeight, panelWidth);

    // 3x3 вокруг игрока
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {

            int y = p.y + dy;
            int x = p.x + dx;

            TerminalUtils::moveCursor(row + 1 + (dy+1), col + 2 + (dx+1));

            if (y < 0 || x < 0 || y >= map.size() || x >= map[0].size()) {
                std::cout << " ";
                continue;
            }

            if (x == p.x && y == p.y) {
                std::cout << "\033[1;32m@\033[0m";
                continue;
            }

            char tile = map[y][x];

            std::cout << colorOf(tile) << tile << "\033[0m";
        }
    }
}
