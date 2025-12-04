#include "ui/FrameDrawer.h"
#include "ui/TerminalUtils.h"
#include <iostream>
#include <string>

void FrameDrawer::drawFrame(size_t row, size_t col, size_t height, size_t width) {
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

void FrameDrawer::drawFrame(size_t row, size_t col, size_t height, size_t width, const std::string& title) {
    TerminalUtils::moveCursor(row, col);
    std::cout << TL;

    size_t availableSpace = width - 2;
    size_t titleLength = title.length();

    // Если заголовок слишком длинный, обрезаем его
    std::string displayTitle = title;
    if (titleLength > availableSpace - 2) {
        displayTitle = title.substr(0, availableSpace - 3) + ".";
        titleLength = availableSpace - 2;
    }

    size_t titlePos = (availableSpace - titleLength) / 2;

    for (int i = 0; i < titlePos; i++) std::cout << H;

    std::cout << " " << displayTitle << " ";

    size_t rightHCount = availableSpace - titlePos - titleLength - 2;
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