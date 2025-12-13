#include "ui/StatusPanel.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include <iostream>

StatusPanel::StatusPanel(Model& model) : model(model) {}

void StatusPanel::draw(const PanelMetrics& pm) const {
    const auto& p = model.getPlayer();

    FrameDrawer::drawFrame(pm.row, pm.col, pm.height, pm.width);

    TerminalUtils::moveCursor(pm.row + 1, pm.col + 2);
    std::cout << "Игрок";

    TerminalUtils::moveCursor(pm.row + 2, pm.col + 2);
    std::cout << "Позиция: (" << p.getX() << ", " << p.getY() << ")";

    TerminalUtils::moveCursor(pm.row + 3, pm.col + 2);
    std::cout << "HP: " << p.getHealth();

    TerminalUtils::moveCursor(pm.row + 4, pm.col + 2);
    std::cout << "Деньги: " << p.getMoney();

    TerminalUtils::moveCursor(pm.row + 5, pm.col + 2);
    std::cout << "Жетоны: " << p.getBadges();

    TerminalUtils::moveCursor(pm.row + 6, pm.col + 2);
    std::cout << "Флирт: " << p.getFlirt();

}