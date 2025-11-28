#include "ui/ActionPanel.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include <iostream>

void ActionPanel::draw(int row, int col, int width) {
    int height = 6;
    FrameDrawer::drawFrame(row, col, height, width);

    TerminalUtils::moveCursor(row + 1, col + 2);
    std::cout << "Действия:";

    TerminalUtils::moveCursor(row + 2, col + 2);
    std::cout << "- (пока пусто)";
}
