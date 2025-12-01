#include "ui/ActionPanel.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include "model/dialogue/Dialogue.h"
#include <iostream>
#include <sstream>

ActionPanel::ActionPanel(const Model& model) : model(model) {}


void ActionPanel::draw(int row, int col, int width) const {
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

    // Вычисляем высоту на основе содержимого
    int text_max_width = width - 4; // учитываем отступы по бокам
    std::vector<std::string> text_lines = wrapText(node->text, text_max_width);
    int text_height = text_lines.size();

    int choices_height = 0;
    std::vector<std::vector<std::string>> choice_lines_list;
    for (const auto& choice : node->choices) {
        std::vector<std::string> choice_lines = wrapText(choice.text, text_max_width - 4); // учитываем номер и отступ
        choice_lines_list.push_back(choice_lines);
        choices_height += choice_lines.size();
    }

    int height = 8 + text_height + choices_height; // заголовок + текст + варианты + управление

    FrameDrawer::drawFrame(row, col, height, width);

    // Заголовок
    TerminalUtils::moveCursor(row + 1, col + 2);
    std::cout << "💬 Диалог с " << node->speaker;

    // Текст диалога
    for (size_t i = 0; i < text_lines.size(); ++i) {
        TerminalUtils::moveCursor(row + 3 + i, col + 2);
        std::cout << text_lines[i];
    }

    int choices_start_row = row + 3 + text_height + 1;

    // Варианты ответов
    TerminalUtils::moveCursor(choices_start_row, col + 2);
    std::cout << "Ваши ответы:";

    int current_choice_row = choices_start_row + 1;
    for (size_t i = 0; i < node->choices.size(); ++i) {
        const auto& choice_lines = choice_lines_list[i];
        for (size_t j = 0; j < choice_lines.size(); ++j) {
            TerminalUtils::moveCursor(current_choice_row + j, col + 4);
            if (j == 0) {
                std::cout << (i + 1) << ". " << choice_lines[j];
            } else {
                std::cout << "   " << choice_lines[j]; // выравнивание для перенесенных строк
            }
        }
        current_choice_row += choice_lines.size();
    }

    // Подсказка управления
    TerminalUtils::moveCursor(row + height - 1, col + 2);
    std::cout << "Нажмите 1-" << node->choices.size() << " для выбора";
}


// Вспомогательная функция для подсчета реальной ширины строки
int ActionPanel::getStringWidth(const std::string& str) const {
    int width = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = str[i];
        // Кириллица в UTF-8 занимает 2 байта и 1 позицию в терминале
        if ((c & 0xE0) == 0xC0) { // 2-байтовый символ
            width += 1;
            i += 2;
        }
        // Эмодзи и специальные символы могут занимать больше, но для простоты считаем 1
        else {
            width += 1;
            i += 1;
        }
    }
    return width;
}

// Вспомогательная функция для переноса текста
std::vector<std::string> ActionPanel::wrapText(const std::string& text, int max_width) const {
    std::vector<std::string> lines;
    std::string current_line;

    std::istringstream stream(text);
    std::string word;

    while (stream >> word) {
        int word_width = getStringWidth(word);
        int current_width = getStringWidth(current_line);

        if (current_line.empty()) {
            current_line = word;
        } else if (current_width + 1 + word_width <= max_width) {
            current_line += " " + word;
        } else {
            lines.push_back(current_line);
            current_line = word;
        }
    }

    if (!current_line.empty()) {
        lines.push_back(current_line);
    }

    return lines;
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