#include "view/View.h"
#include "ui/TerminalUtils.h"
#include "ui/StatusPanel.h"
#include "ui/ActionPanel.h"
#include "ui/MapRenderer.h"
#include <iostream>

View::View(Model& m)
    :
    model(m),
    statusPanel(m),
    mapRenderer(m),
    actionPanel(m) {
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

    constexpr size_t RIGHT_WIDTH = 22;
    const size_t rightCol = cols - RIGHT_WIDTH - 1;
    const size_t actionPanelWidth = rightCol - 2;

    constexpr int radiusY = 4;
    constexpr int radiusX = 10;

    PanelMetrics statusPM = {12, rightCol, 10, radiusX * 2 + 3};
    PanelMetrics actionPM = {1, 1, cols, actionPanelWidth};
    PanelMetrics mapPM = {1, rightCol, radiusY * 2 + 3, radiusX * 2 + 3};

    statusPanel.draw(statusPM);
    actionPanel.draw(actionPM);
    mapRenderer.draw(mapPM, radiusY, radiusX);

    // const auto& messages = DebugLog::instance().getMessages();
    // size_t debugStartRow = rows - messages.size() - 1;
    // size_t row = debugStartRow;
    // for (const auto& msg : messages) {
    //     TerminalUtils::moveCursor(row++, 1);
    //     std::cout << msg << std::string(cols - msg.size(), ' ');
    // }

    std::cout.flush();
}

