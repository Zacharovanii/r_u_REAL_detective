#include "ui/ActionPanel.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include "model/dialogue/Dialogue.h"
#include <iostream>
#include <sstream>

ActionPanel::ActionPanel(const Model& model) : model(model) {}

void ActionPanel::draw(int row, int col, int width) const {
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
    // Вычисляем высоту: заголовок + по строке на каждый объект + подсказка
    size_t height = 3 + interactables.size();
    FrameDrawer::drawFrame(row, col, height, width);
    // Заголовок
    TerminalUtils::moveCursor(row + 1, col + 2);
    std::cout << "📡 Объектов рядом (" << interactables.size() << "):";

    // Список объектов с номерами
    for (int i = 0; i < interactables.size(); ++i) {
        const auto* interactable = interactables[i];
        TerminalUtils::moveCursor(row + 2 + i, col + 4);
        // Форматируем строку: номер, имя, описание
        std::cout << i + 1 << ". " << interactable->getName();
        // Если есть место, добавляем описание
        if (width > 30) {
            std::cout << " - " << interactable->getDescription();
        }
    }
    // Подсказка управления
    TerminalUtils::moveCursor(row + height - 1, col + 2);
    if (interactables.size() != 1) {
        std::cout << "Нажмите 1-" << interactables.size() << " для взаимодействия";
    } else {
        std::cout << "Нажмите 1 для взаимодействия";
    }
}

void ActionPanel::drawDialogue(int row, int col, int width, const DialogueNode* node) {
    // Вычисляем высоту на основе содержимого
    int text_max_width = width - 4; // учитываем отступы по бокам
    std::vector<std::string> text_lines = wrapText(node->text, text_max_width);
    size_t text_height = text_lines.size();

    size_t choices_height = 0;
    std::vector<std::vector<std::string>> choice_lines_list;
    for (const auto& choice : node->choices) {
        std::vector<std::string> choice_lines = wrapText(choice.text, text_max_width - 4); // учитываем номер и отступ
        choice_lines_list.push_back(choice_lines);
        choices_height += choice_lines.size();
    }

    size_t height = 8 + text_height + choices_height; // заголовок + текст + варианты + управление

    FrameDrawer::drawFrame(row, col, height, width);

    // Заголовок
    TerminalUtils::moveCursor(row + 1, col + 2);
    std::cout << "💬 Диалог с " << node->speaker;

    // Текст диалога
    for (size_t i = 0; i < text_lines.size(); ++i) {
        TerminalUtils::moveCursor(row + 3 + i, col + 2);
        std::cout << text_lines[i];
    }

    size_t choices_start_row = row + 3 + text_height + 1;

    // Варианты ответов
    TerminalUtils::moveCursor(choices_start_row, col + 2);
    std::cout << "Ваши ответы:";

    size_t current_choice_row = choices_start_row + 1;
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
    if (node->choices.size() != 1)
        std::cout << "Нажмите 1-" << node->choices.size() << " для выбора";
    else
        std::cout << "Нажмите 1 для выбора";
}

void ActionPanel::drawEmpty(int row, int col, int width) {
    int height = 8;
    FrameDrawer::drawFrame(row, col, height, width);

    int c = col + 2;
    for (int r = 0; r < EMPTY_PANEL_LINES_COUNT; r++) {
        TerminalUtils::moveCursor(row + r + 1, c);
        std::cout << EMPTY_PANEL_TEXT[r];
    }
}


// Вспомогательная функция для подсчета реальной ширины строки
int ActionPanel::getStringWidth(const std::string& str) {
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
std::vector<std::string> ActionPanel::wrapText(const std::string& text, int max_width) {
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