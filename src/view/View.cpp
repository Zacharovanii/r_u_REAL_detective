#include "view/View.h"
#include "ui/TerminalUtils.h"
#include "ui/StatusPanel.h"
#include "ui/ActionPanel.h"
#include "ui/MapRenderer.h"
#include <iostream>

View::View(const Model& m) : model(m), mapRenderer(m), actionPanel(m) {
    TerminalUtils::clearScreen();
    TerminalUtils::hideCursor();
}

View::~View() {
    TerminalUtils::clearScreen();
    TerminalUtils::showCursor();
}

void View::draw() const {
    size_t rows, cols;
    TerminalUtils::getTerminalSize(rows, cols);
    TerminalUtils::clearScreen();

    constexpr int RIGHT_WIDTH = 22;
    const int rightCol = static_cast<int>(cols) - RIGHT_WIDTH - 1;  // Правый край
    const int actionPanelWidth = rightCol - 2;

    StatusPanel::draw(model, 12, rightCol, RIGHT_WIDTH + 1);
    actionPanel.draw(1, 1, actionPanelWidth);
    mapRenderer.draw(1, rightCol, 4, 10);

    std::cout.flush();
}

