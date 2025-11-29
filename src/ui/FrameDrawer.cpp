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

void FrameDrawer::drawFrame(int row, int col, int height, int width, const std::string& title) {
    const char* TL = "┌";
    const char* TR = "┐";
    const char* BL = "└";
    const char* BR = "┘";
    const char* H  = "─";
    const char* V  = "│";

    TerminalUtils::moveCursor(row, col);
    std::cout << TL;

    int availableSpace = width - 2;
    int titleLength = static_cast<int>(title.length());

    // Если заголовок слишком длинный, обрезаем его
    std::string displayTitle = title;
    if (titleLength > availableSpace - 2) {
        displayTitle = title.substr(0, availableSpace - 3) + ".";
        titleLength = availableSpace - 2;
    }

    int titlePos = (availableSpace - titleLength) / 2;

    for (int i = 0; i < titlePos; i++) std::cout << H;

    std::cout << " " << displayTitle << " ";

    int rightHCount = availableSpace - titlePos - titleLength - 2;
    for (int i = 0; i < rightHCount; i++) std::cout << H;

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