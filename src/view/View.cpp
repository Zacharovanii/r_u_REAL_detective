#include "view/View.h"
#include "ui/TerminalUtils.h"
#include "ui/StatusPanel.h"
#include "ui/ActionPanel.h"
#include "ui/MapRenderer.h"
#include <iostream>

View::View(const Model& m) : model(m) {}

void View::draw() {
    int rows, cols;
    TerminalUtils::getTerminalSize(rows, cols);

    TerminalUtils::clearScreen();

    // Левая панель
    StatusPanel::draw(model, 1, 1, 30);

    // Центр
    ActionPanel::draw(1, cols/2 - 15, 40);

    // Правая карта
    mapRenderer.draw(model, 1, cols - 15, 5);

    TerminalUtils::hideCursor();
    std::cout.flush();
}
