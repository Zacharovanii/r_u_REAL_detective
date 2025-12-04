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

    // constexpr int LEFT_WIDTH = 30;    // Статус-панель
    constexpr int RIGHT_WIDTH = 22;   // Карта
    constexpr int CENTER_WIDTH = 40;  // Действия

    constexpr int leftCol = 1;
    const int rightCol = cols - RIGHT_WIDTH - 1;                // Справа
    // const int centerCol = cols / 2 - CENTER_WIDTH / 3 - 1;  // По центру

    StatusPanel::draw(model, 12, rightCol, RIGHT_WIDTH + 1);
    actionPanel.draw(1, leftCol, CENTER_WIDTH);
    mapRenderer.draw(1, rightCol, 4, 10);

    TerminalUtils::moveCursor(rows - 15, 1);

    std::cout.flush();
}
