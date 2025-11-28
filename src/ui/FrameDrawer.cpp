#include "ui/FrameDrawer.h"
#include "ui/TerminalUtils.h"
#include <iostream>

void FrameDrawer::drawFrame(int row, int col, int height, int width) {
    const char* TL = "┌";
    const char* TR = "┐";
    const char* BL = "└";
    const char* BR = "┘";
    const char* H  = "─";
    const char* V  = "│";

    TerminalUtils::moveCursor(row, col);
    std::cout << TL;
    for (int i = 0; i < width - 2; i++) std::cout << H;
    std::cout << TR;

    for (int r = 1; r < height - 1; r++) {
        TerminalUtils::moveCursor(row + r, col);
        std::cout << V;

        TerminalUtils::moveCursor(row + r, col + width - 1);
        std::cout << V;
    }

    TerminalUtils::moveCursor(row + height - 1, col);
    std::cout << BL;
    for (int i = 0; i < width - 2; i++) std::cout << H;
    std::cout << BR;
}
