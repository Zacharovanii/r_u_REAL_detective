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
void FrameDrawer::drawFrame(PanelMetrics pm) {
    drawFrame(pm.row, pm.col, pm.height, pm.width);
}
void FrameDrawer::drawTitle(PanelMetrics pm, const std::string& title) {
    if (pm.height < 2) return;

    size_t availableSpace = pm.width - 2;
    size_t titleLength = title.length();

    // Если заголовок слишком длинный, обрезаем его
    std::string displayTitle = title;
    if (titleLength > availableSpace - 2) {
        displayTitle = title.substr(0, availableSpace - 3) + ".";
        titleLength = availableSpace - 2;
    }
    size_t titlePos = (availableSpace - titleLength) / 2;

    TerminalUtils::moveCursor(pm.row, pm.col + 1 + titlePos);
    std::cout << " " << displayTitle << " ";
}
void FrameDrawer::drawTitle(PanelMetrics pm, const StyledText& title) {
    if (pm.height < 2) return;

    size_t titlePos = pm.width / 2 - title.getText().length() / 3;
    TerminalUtils::moveCursor(pm.row, pm.col + titlePos);
    std::cout << " " << title.getStyledText() << " ";
}
void FrameDrawer::drawHint(PanelMetrics pm, const std::string& hint) {
    if (pm.height < 2) return;

    size_t availableSpace = pm.width - 2;
    size_t hintLength = hint.length();

    // Если подсказка слишком длинная, обрезаем ее
    std::string displayHint = hint;
    if (hintLength > availableSpace - 2) {
        displayHint = hint.substr(0, availableSpace - 3) + ".";
        hintLength = availableSpace - 2;
    }

    size_t hintPos = (availableSpace - hintLength) / 2;

    // Рисуем подсказку поверх нижней границы
    TerminalUtils::moveCursor(pm.row + pm.height - 1, pm.col + 1 + hintPos);
    std::cout << " " << displayHint << " ";
}

void FrameDrawer::drawFrameWithTitle(PanelMetrics pm, const std::string& title) {
    drawFrame(pm);
    drawTitle(pm, title);
}
void FrameDrawer::drawFrameWithTitle(PanelMetrics pm, const StyledText& title) {
    drawFrame(pm);
    drawTitle(pm, title);
}
void FrameDrawer::drawFrameWithHint(PanelMetrics pm, const std::string& hint) {
    drawFrame(pm);
    drawHint(pm, hint);
}
void FrameDrawer::drawFrameWithTitleAndHint(PanelMetrics pm, const std::string& title, const std::string& hint) {
    drawFrame(pm);
    drawTitle(pm, title);
    drawHint(pm, hint);
}