#include "ui/StatusPanel.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include <iostream>

void StatusPanel::draw(const Model& model, int row, int col, int width) {
    const auto& p = model.getPlayer();

    int height = 8;
    FrameDrawer::drawFrame(row, col, height, width);

    TerminalUtils::moveCursor(row + 1, col + 2);
    std::cout << "Игрок";

    TerminalUtils::moveCursor(row + 2, col + 2);
    std::cout << "Позиция: (" << p.x << ", " << p.y << ")";

    TerminalUtils::moveCursor(row + 3, col + 2);
    std::cout << "HP: " << p.hp;

    TerminalUtils::moveCursor(row + 4, col + 2);
    std::cout << "Статус: " << p.status;
}
