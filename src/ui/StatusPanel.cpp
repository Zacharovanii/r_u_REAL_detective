#include "ui/StatusPanel.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include <iostream>

void StatusPanel::draw(const Model& model, int row, int col, int width) {
    const auto& p = model.getPlayer();

    int height = 10;
    FrameDrawer::drawFrame(row, col, height, width);

    TerminalUtils::moveCursor(row + 1, col + 2);
    std::cout << "Игрок";

    TerminalUtils::moveCursor(row + 2, col + 2);
    std::cout << "Позиция: (" << p.getX() << ", " << p.getY() << ")";

    TerminalUtils::moveCursor(row + 3, col + 2);
    std::cout << "HP: " << p.getHealth();

    TerminalUtils::moveCursor(row + 4, col + 2);
    std::cout << "Деньги: " << p.getMoney();

    TerminalUtils::moveCursor(row + 5, col + 2);
    std::cout << "Жетоны: " << p.getBadges();

    TerminalUtils::moveCursor(row + 6, col + 2);
    std::cout << "Флирт: " << p.getFlirt();

    TerminalUtils::moveCursor(row + 7, col + 2);
    std::cout << "Статус: " << p.getStatus();
}