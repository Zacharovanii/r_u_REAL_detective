#include "ui/ActionPanel.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include "model/dialogue/Dialogue.h"
#include "helpers/TextWrapper.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// ==================== КОНСТРУКТОР ====================
ActionPanel::ActionPanel(const Model& model) : model(model) {}

// ==================== ОСНОВНОЙ МЕТОД ОТРИСОВКИ ====================
void ActionPanel::draw(int row, int col, int width) const {
    if (width <= 0 || row < 0 || col < 0) {
        return; // Некорректные параметры
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

// ==================== МЕТОДЫ РАСЧЁТА РАЗМЕРОВ ====================
size_t ActionPanel::calculateInteractablesHeight(size_t itemCount) {
    return 3 + itemCount > 8 ? 3 + itemCount : 8; // заголовок + элементы + подсказка
}

DialogueLayout ActionPanel::calculateDialogueLayout(const DialogueNode* node, int availableWidth) {
    DialogueLayout layout;
    // Рассчитываем текст диалога
    const int textMaxWidth = availableWidth - PANEL_PADDING * 2;
    layout.textLines = TextWrapper::wrap(node->text, textMaxWidth);

    // Рассчитываем варианты ответов
    const int choiceMaxWidth = textMaxWidth - 2; // дополнительный отступ для номеров
    for (size_t i = 0; i < node->choices.size(); ++i) {
        auto lines = TextWrapper::wrap(node->choices[i].text, choiceMaxWidth);
        layout.choicesData.push_back({i + 1, std::move(lines)});
    }

    // Рассчитываем общую высоту
    size_t textHeight = layout.textLines.size();
    size_t choicesHeight = 0;
    for (const auto& choice : layout.choicesData) {
        choicesHeight += choice.lines.size();
    }

    layout.totalHeight = 8 + textHeight + choicesHeight; // базово 8 строк
    return layout;
}

// ==================== КОМПОНЕНТЫ ОТРИСОВКИ ====================

void ActionPanel::drawPanelFrame(int row, int col, size_t height, int width,
                                const std::string& title) {
    if (title.empty()) {
        FrameDrawer::drawFrame(row, col, height, width);
    } else {
        FrameDrawer::drawFrame(row, col, height, width, title);
    }
}

void ActionPanel::drawTitle(int row, int col, const std::string& title,
                           const std::string& icon) {
    TerminalUtils::moveCursor(row, col);
    if (!icon.empty()) {
        std::cout << icon << " ";
    }
    std::cout << title;
}

void ActionPanel::drawTextLines(int startRow, int startCol,
                               const std::vector<std::string>& lines) {
    for (size_t i = 0; i < lines.size(); ++i) {
        TerminalUtils::moveCursor(startRow + static_cast<int>(i), startCol);
        std::cout << lines[i];
    }
}

void ActionPanel::drawNumberedList(int startRow, int startCol,
                                  const std::vector<const Interactable*>& items,
                                  int availableWidth) {
    for (size_t i = 0; i < items.size(); ++i) {
        TerminalUtils::moveCursor(startRow + static_cast<int>(i), startCol);

        const auto* item = items[i];
        std::cout << (i + 1) << ". " << item->getName();

        // Добавляем описание, если есть место
        if (shouldShowDescription(availableWidth) && !item->getDescription().empty()) {
            std::cout << " - " << item->getDescription();
        }
    }
}

void ActionPanel::drawChoicesList(int startRow, int startCol,
                                 const std::vector<ChoiceData>& choicesData) {
    size_t currentRow = 0;

    for (const auto& choice : choicesData) {
        for (size_t lineIdx = 0; lineIdx < choice.lines.size(); ++lineIdx) {
            TerminalUtils::moveCursor(startRow + static_cast<int>(currentRow + lineIdx),
                                     startCol);

            if (lineIdx == 0) {
                // Первая строка варианта с номером
                std::cout << std::setw(2) << choice.number << ". " << choice.lines[lineIdx];
            } else {
                // Последующие строки (перенос) с выравниванием
                std::cout << "    " << choice.lines[lineIdx];
            }
        }
        currentRow += choice.lines.size();
    }
}

void ActionPanel::drawControlHint(int row, int col, size_t itemCount,
                                 const std::string& action) {
    TerminalUtils::moveCursor(row, col);

    if (itemCount == 0) {
        std::cout << "Нет доступных действий";
    } else if (itemCount == 1) {
        std::cout << "Нажмите 1 для " << action;
    } else {
        std::cout << "Нажмите 1-" << itemCount << " для " << action;
    }
}

// ==================== ОСНОВНЫЕ ПАНЕЛИ ====================

void ActionPanel::drawInteractablesList(int row, int col, int width) const {
    const auto& interactables = model.getNearbyInteractables();
    if (interactables.empty()) {
        drawEmpty(row, col, width);
        return;
    }

    // Расчёт и отрисовка рамки
    const size_t height = calculateInteractablesHeight(interactables.size());
    drawPanelFrame(row, col, height, width);

    // Заголовок
    std::ostringstream title;
    title << "Объектов рядом (" << interactables.size() << "):";
    drawTitle(row + 1, col + TITLE_INDENT, title.str(), "📡");

    // Список объектов
    const int listStartCol = col + CONTENT_INDENT;
    const int listStartRow = row + 2;
    const int availableWidth = width - CONTENT_INDENT - PANEL_PADDING;

    drawNumberedList(listStartRow, listStartCol, interactables, availableWidth);

    // Подсказка управления
    const int hintRow = row + static_cast<int>(height) - 1;
    drawControlHint(hintRow, col + TITLE_INDENT, interactables.size());
}

void ActionPanel::drawDialogue(int row, int col, int width, const DialogueNode* node) {
    if (!node) {
        drawEmpty(row, col, width);
        return;
    }

    // Расчёт макета
    const int availableWidth = width;
    const DialogueLayout layout = calculateDialogueLayout(node, availableWidth);

    // Отрисовка рамки
    drawPanelFrame(row, col, layout.totalHeight, width);

    // Заголовок диалога
    std::ostringstream title;
    title << "Диалог с " << node->speaker;
    drawTitle(row + 1, col + TITLE_INDENT, title.str(), "💬");

    // Текст диалога
    const int textStartRow = row + 3;
    drawTextLines(textStartRow, col + TITLE_INDENT, layout.textLines);

    // Заголовок вариантов ответа
    const int choicesTitleRow = textStartRow + static_cast<int>(layout.textLines.size()) + 1;
    drawTitle(choicesTitleRow, col + TITLE_INDENT, "Ваши ответы:");

    // Варианты ответов
    const int choicesStartRow = choicesTitleRow + 1;
    const int choicesStartCol = col + CONTENT_INDENT;
    drawChoicesList(choicesStartRow, choicesStartCol, layout.choicesData);

    // Подсказка управления
    const int hintRow = row + static_cast<int>(layout.totalHeight) - 1;
    drawControlHint(hintRow, col + TITLE_INDENT, node->choices.size(), "выбора");
}

void ActionPanel::drawEmpty(int row, int col, int width) {
    drawPanelFrame(row, col, EMPTY_PANEL_HEIGHT, width);

    const int textStartCol = col + TITLE_INDENT;
    for (size_t i = 0; i < EMPTY_PANEL_LINES.size(); ++i) {
        TerminalUtils::moveCursor(row + static_cast<int>(i) + 1, textStartCol);
        std::cout << EMPTY_PANEL_LINES[i];
    }
}