#include "ui/ActionPanel.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include "model/Dialogue.h"
#include <iostream>

ActionPanel::ActionPanel(const Model& model) : model(model) {}


void ActionPanel::draw(int row, int col, int width) const {
    // Проверяем, активен ли диалог;
    if (model.getDialogueManager().isInDialogue()) {
        drawDialogue(row, col, width, model.getDialogueManager().getCurrentDialogue());
    } else {
        drawEmpty(row, col, width);
    }
}

void ActionPanel::drawDialogue(int row, int col, int width, const Dialogue* dialogue) const {
    if (!dialogue) {
        drawEmpty(row, col, width);
        return;
    }

    const DialogueNode* node = dialogue->getCurrentNode();
    if (!node) {
        drawEmpty(row, col, width);
        return;
    }

    // Вычисляем высоту на основе количества вариантов ответа
    int height = 20 + node->choices.size(); // базовая высота + варианты

    FrameDrawer::drawFrame(row, col, height, width);

    // Заголовок
    TerminalUtils::moveCursor(row + 1, col + 2);
    std::cout << "💬 Диалог с " << node->speaker;

    // Текст диалога
    TerminalUtils::moveCursor(row + 3, col + 2);

    // Перенос текста
    std::string text = node->text;
    size_t pos = 0;
    size_t max_line_length = width - 4; // учитываем отступы

    while (pos < text.length()) {
        TerminalUtils::moveCursor(row + 3 + (pos / max_line_length), col + 2);
        size_t end_pos = std::min(pos + max_line_length, text.length());
        std::cout << text.substr(pos, end_pos - pos);
        pos = end_pos;
    }

    int text_height = (text.length() + max_line_length - 1) / max_line_length;
    int choices_start_row = row + 3 + text_height + 1;

    // Варианты ответов
    TerminalUtils::moveCursor(choices_start_row, col + 2);
    std::cout << "Ваши ответы:";

    for (size_t i = 0; i < node->choices.size(); ++i) {
        TerminalUtils::moveCursor(choices_start_row + 1 + i, col + 4);
        std::cout << (i + 1) << ". " << node->choices[i].text;
    }

    // Подсказка управления
    TerminalUtils::moveCursor(row + height - 1, col + 2);
    std::cout << "Нажмите 1-" << node->choices.size() << " для выбора";
}

void ActionPanel::drawEmpty(int row, int col, int width) const {
    int height = 6;
    FrameDrawer::drawFrame(row, col, height, width);

    TerminalUtils::moveCursor(row + 1, col + 2);
    std::cout << "Действия:";

    TerminalUtils::moveCursor(row + 2, col + 2);
    std::cout << "Подойдите к персонажу";

    TerminalUtils::moveCursor(row + 3, col + 2);
    std::cout << "для начала диалога";

    TerminalUtils::moveCursor(row + 4, col + 2);
    std::cout << "Управление: WASD";
}