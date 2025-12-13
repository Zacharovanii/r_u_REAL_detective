#include "ui/ActionPanel.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include "helpers/TextWrapper.h"
#include <iostream>

ActionPanel::ActionPanel(Model& model) : model(model) {}

void ActionPanel::draw(const PanelMetrics& pm) const {
    TerminalUtils::moveCursor(pm.row, pm.col);
    TerminalUtils::moveCursor(pm.row + 2, pm.col + 1);

    if (model.isInDialogue()) {
        drawDialogue(pm);
    } else if (!model.getNearbyInteractables().empty()) {
        drawNearbyItems(pm);
    } else {
        drawEmpty(pm);
    }
}

void ActionPanel::drawDialogue(PanelMetrics pm) const {
    TerminalUtils::moveCursor(pm.row, pm.col);
    auto dialogue = model.getDialogueManager().getCurrentDialogue();
    auto node = dialogue->getCurrentNode();
    StyledText title = {node->speaker(), Color::BrightYellow, Style::Blink};
    FrameDrawer::drawFrameWithTitle(pm, title);

    size_t s_row = pm.row + 1, s_col = pm.col + 2;
    auto lines = TextWrapper::wrap(node->text(), pm.width - 2);
    for (const auto& line : lines) {
        TerminalUtils::moveCursor(s_row, s_col);
        std::cout << line;
        s_row++;
    }
    s_row++;
    s_col += 2;
    auto items = node->choices();
    auto item_count = items.size();
    for (int i = 0; i < item_count; i++) {
        TerminalUtils::moveCursor(s_row + i, s_col);
        std::cout << i + 1 << ". " << items[i].text;
    }
}

void ActionPanel::drawNearbyItems(PanelMetrics pm) const {
    TerminalUtils::moveCursor(pm.row, pm.col);
    StyledText title = {"Выбор взаимодействия", Color::BrightCyan, Style::Blink};
    FrameDrawer::drawFrameWithTitle(pm, title);

    size_t s_row = pm.row + 1, s_col = pm.col + 2;
    TerminalUtils::moveCursor(s_row, s_col);
    std::cout << "Нажмите 1-9 для выбора:";
    s_row++;
    s_col += 2;
    auto items = model.getNearbyInteractables();
    auto item_count = items.size();
    for (int i = 0; i < item_count; i++) {
        TerminalUtils::moveCursor(s_row + i, s_col);
        std::cout << i + 1 << ". " << items[i]->getName() << ": " << items[i]->getDescription() ;
    }
}


void ActionPanel::drawEmpty(const PanelMetrics& pm) const {
    TerminalUtils::moveCursor(pm.row, pm.col);
    StyledText title = {"Исследование", Color::BrightRed, Style::Blink};
    FrameDrawer::drawFrameWithTitle(pm, title);

    size_t s_row = pm.row + 1, s_col = pm.col + 2;
    TerminalUtils::moveCursor(s_row, s_col);
    std::cout << about[0];
    s_col++;
    for (int line = 1; line < 6; line++) {
        TerminalUtils::moveCursor(s_row + line, s_col);
        std::cout << about[line];
    }
}