#include "ui/ActionPanel.h"
#include <sstream>

// ==================== КОНСТРУКТОР ====================
ActionPanel::ActionPanel(const Model& model) : model(model) {}

// ==================== ОСНОВНОЙ МЕТОД ОТРИСОВКИ ====================
void ActionPanel::draw(int row, int col, int width) const {
    if (width <= 0 || row < 0 || col < 0) {
        return;
    }
    if (model.isInDialogue()) {
        const Dialogue* dialogue = model.getDialogueManager().getCurrentDialogue();
        if (const DialogueNode* node = dialogue ? dialogue->getCurrentNode() : nullptr) {
            drawDialogue(row, col, width, node);
        } else {
            drawEmpty(row, col, width);
        }
    } else if (!model.getNearbyInteractables().empty()) {
        drawInteractablesList(row, col, width);
    } else {
        drawEmpty(row, col, width);
    }
}

// ==================== ПАНЕЛЬ ИНТЕРАКТИВНЫХ ОБЪЕКТОВ ====================
void ActionPanel::drawInteractablesList(int row, int col, int width) const {
    const auto& interactables = model.getNearbyInteractables();

    // Если объектов нет - пустая панель
    if (interactables.empty()) {
        drawEmpty(row, col, width);
        return;
    }
    // Расчёт макета
    auto metrics = ActionPanelLayout::calculateInteractablesLayout(interactables.size());
    bool showDescriptions = ActionPanelLayout::shouldShowDescription(width);

    PanelComponents::drawPanelFrame(row, col, metrics.height, width);

    std::ostringstream title;
    title << "Объектов рядом (" << interactables.size() << "):";

    PanelComponents::drawTitle(row + 1, col + 2, title.str(), "📡");
    PanelComponents::drawNumberedList(row + 2, col + 4, interactables, showDescriptions);
    PanelComponents::drawControlHint(row + static_cast<int>(metrics.height) - 1,
                                    col + 2,
                                    interactables.size());
}
// ==================== ПАНЕЛЬ ДИАЛОГА ====================
void ActionPanel::drawDialogue(int row, int col, int width, const DialogueNode* node) const {
    auto layout = ActionPanelLayout::calculateDialogueLayout(node, width);
    PanelComponents::drawPanelFrame(row, col, layout.totalHeight, width);

    std::ostringstream title;
    title << "Диалог с " << node->speaker;
    PanelComponents::drawTitle(row + 1, col + 2, title.str(), "💬");
    PanelComponents::drawTextLines(row + 3, col + 2, layout.textLines);

    const int choicesTitleRow = row + 3 + static_cast<int>(layout.textLines.size()) + 1;
    PanelComponents::drawTitle(choicesTitleRow, col + 2, "Ваши ответы:");
    PanelComponents::drawChoicesList(choicesTitleRow + 1, col + 4, layout.choicesData);

    const int hintRow = row + static_cast<int>(layout.totalHeight) - 1;
    PanelComponents::drawControlHint(hintRow, col + 2,
                                    node->choices.size(), "выбора");
}

// ==================== ПУСТАЯ ПАНЕЛЬ ====================
void ActionPanel::drawEmpty(int row, int col, int width) const {
    PanelComponents::drawEmptyPanel(row, col, width);
}