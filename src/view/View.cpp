#include "view/View.h"
#include "ui/TerminalUtils.h"
#include "ui/StatusPanel.h"
#include "ui/ActionPanel.h"
#include "ui/MapRenderer.h"
#include <iostream>

View::View(const Model& m) : model(m), mapRenderer(m) {}

View::~View() {
    TerminalUtils::clearScreen();
    TerminalUtils::showCursor();
}

void View::draw() const {
    int rows, cols;
    TerminalUtils::getTerminalSize(rows, cols);

    TerminalUtils::clearScreen();

    // Левая панель
    StatusPanel::draw(model, 1, 1, 30);

    // Центр
    ActionPanel::draw(1, cols/2 - 20, 40);

    // Правая карта
    mapRenderer.draw(1, cols - 22, 4, 10);

    TerminalUtils::hideCursor();
    std::cout.flush();
}
