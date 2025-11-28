#include "view/View.h"
#include "ui/TerminalUtils.h"
#include "ui/StatusPanel.h"
#include "ui/ActionPanel.h"
#include "ui/MapRenderer.h"
#include <iostream>

View::View(const Model& m) : model(m), mapRenderer(m) {
    TerminalUtils::clearScreen();
    TerminalUtils::hideCursor();
}

View::~View() {
    TerminalUtils::clearScreen();
    TerminalUtils::showCursor();
}

void View::draw() const {
    int rows, cols;
    TerminalUtils::getTerminalSize(rows, cols);
    TerminalUtils::clearScreen();

    // Ширины панелей (можно вынести в константы класса)
    constexpr int LEFT_WIDTH = 30;    // Статус-панель
    constexpr int RIGHT_WIDTH = 22;   // Карта
    constexpr int CENTER_WIDTH = 40;  // Действия

    // Позиции
    constexpr int leftCol = 1;                            // Слева
    const int rightCol = cols - RIGHT_WIDTH;          // Справа
    const int centerCol = cols / 2 - CENTER_WIDTH / 3 - 1;  // По центру

    // Отрисовка
    StatusPanel::draw(model, 1, leftCol, LEFT_WIDTH);
    ActionPanel::draw(1, centerCol, CENTER_WIDTH);
    mapRenderer.draw(1, rightCol, 4, 10);

    std::cout.flush();
}
