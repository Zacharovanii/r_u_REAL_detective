#include "view/View.h"
#include "ui/TerminalUtils.h"
#include "ui/StatusPanel.h"
#include "ui/ActionPanel.h"
#include "ui/MapRenderer.h"
#include "helpers/DebugLog.h"
#include <iostream>

View::View(const Model& m) : model(m), mapRenderer(const_cast<Model&>(m)), actionPanel(const_cast<Model&>(m)) {
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

    const auto& messages = DebugLog::instance().getMessages();
    size_t debugStartRow = rows - messages.size() - 1;
    size_t row = debugStartRow;
    for (const auto& msg : messages) {
        TerminalUtils::moveCursor(row++, 1);
        std::cout << msg << std::string(cols - msg.size(), ' ');
    }


    std::cout.flush();
}

