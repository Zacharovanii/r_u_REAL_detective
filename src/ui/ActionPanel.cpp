#include "ui/ActionPanel.h"
#include <iostream>
#include <sstream>

ActionPanel::ActionPanel(const Model& model) : model(model) {
    static bool stylesInitialized = false;
    if (!stylesInitialized) {
        PanelComponents::initStyles();
        stylesInitialized = true;
    }
}

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

void ActionPanel::drawInteractablesList(int row, int col, int width) const {
    const auto& interactables = model.getNearbyInteractables();

    if (interactables.empty()) {
        drawEmpty(row, col, width);
        return;
    }

    auto metrics = ActionPanelLayout::calculateInteractablesLayout(interactables.size());
    bool showDescriptions = ActionPanelLayout::shouldShowDescription(width);

    // Отрисовка
    PanelComponents::drawPanelFrame(row, col, metrics.height, width);

    // Заголовок с эмодзи
    std::ostringstream title;
    title << "Объектов рядом (" << interactables.size() << "):";
    PanelComponents::drawTitle(row + 1, col + 2, title.str(), "📡");

    // Список объектов
    PanelComponents::drawNumberedList(row + 2, col + 4, interactables, showDescriptions);

    // Подсказка управления (подсвечиваем важность)
    PanelComponents::drawControlHint(row + static_cast<int>(metrics.height) - 1,
                                    col + 2,
                                    interactables.size(),
                                    "взаимодействия",
                                    true); // isImportant = true
}

void ActionPanel::drawDialogue(int row, int col, int width, const DialogueNode* node) const {
    if (!node) {
        drawEmpty(row, col, width);
        return;
    }

    auto layout = ActionPanelLayout::calculateDialogueLayout(node, width);

    // Отрисовка
    PanelComponents::drawPanelFrame(row, col, layout.totalHeight, width);

    // Заголовок диалога с именем говорящего
    PanelComponents::drawDialogueSpeaker(row + 1, col + 2, node->speaker);

    // Текст диалога (обычный цвет)
    PanelComponents::drawTextLines(row + 3, col + 2, layout.textLines,
                                  TextStyles::Theme::NormalText);

    // Заголовок вариантов ответа
    const int choicesTitleRow = row + 3 + static_cast<int>(layout.textLines.size()) + 1;
    PanelComponents::drawTitle(choicesTitleRow, col + 2, "Ваши ответы:");

    // Варианты ответов (интерактивные)
    PanelComponents::drawChoicesList(choicesTitleRow + 1, col + 4, layout.choicesData);

    // Подсказка управления (подсвеченная)
    const int hintRow = row + static_cast<int>(layout.totalHeight) - 1;
    PanelComponents::drawControlHint(hintRow, col + 2,
                                    node->choices.size(),
                                    "выбора",
                                    true); // isImportant = true
}

void ActionPanel::drawEmpty(int row, int col, int width) const {
    PanelComponents::drawEmptyPanel(row, col, width);
}