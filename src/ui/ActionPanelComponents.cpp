#include "ui/ActionPanelComponents.h"
#include "ui/ActionPanelLayout.h"
#include <iostream>
#include <iomanip>
#include <sstream>

#include "model/objects/Interactable.h"

// ==================== ИНИЦИАЛИЗАЦИЯ ====================

void PanelComponents::initStyles() {
    TextStyles::init();
}

// ==================== ФРЕЙМ И ЗАГОЛОВОК ====================

void PanelComponents::drawPanelFrame(int row, int col, size_t height, int width,
                                    const std::string& title) {
    if (title.empty()) {
        FrameDrawer::drawFrame(row, col, height, width);
    } else {
        FrameDrawer::drawFrame(row, col, height, width, title);
    }
}

void PanelComponents::drawTitle(int row, int col, const std::string& title,
                               const std::string& icon) {
    TerminalUtils::moveCursor(row, col);

    if (!icon.empty()) {
        // Иконка с особым цветом
        std::cout << TextStyles::styled(icon, TextStyles::Theme::Emoji)
                  << " ";
    }

    // Заголовок с цветом
    std::cout << TextStyles::styled(title, TextStyles::Theme::Title,
                                   TextStyles::Style::Bold);
}

// ==================== ТЕКСТОВЫЕ СТРОКИ ====================

void PanelComponents::drawTextLines(int startRow, int startCol,
                                   const std::vector<std::string>& lines,
                                   TextStyles::Color color,
                                   TextStyles::Style style) {
    for (size_t i = 0; i < lines.size(); ++i) {
        TerminalUtils::moveCursor(startRow + static_cast<int>(i), startCol);
        std::cout << TextStyles::styled(lines[i], color, style);
    }
}

// ==================== СПИСОК С НОМЕРАМИ ====================

void PanelComponents::drawNumberedList(int startRow, int startCol,
                                      const std::vector<Interactable*>& items,
                                      bool showDescriptions) {
    for (size_t i = 0; i < items.size(); ++i) {
        TerminalUtils::moveCursor(startRow + static_cast<int>(i), startCol);

        const auto* item = items[i];
        if (!item) continue;

        // Номер
        std::cout << TextStyles::styled(std::to_string(i + 1) + ". ",
                                       TextStyles::Theme::Number,
                                       TextStyles::Style::Bold);

        // Имя объекта
        std::cout << applyItemStyle(item, item->getName());

        // Описание (если нужно и есть)
        if (showDescriptions && !item->getDescription().empty()) {
            std::cout << " - "
                     << TextStyles::styled(item->getDescription(),
                                          TextStyles::Theme::Description);
        }
    }
}

// ==================== СПИСОК ВАРИАНТОВ ====================

void PanelComponents::drawChoicesList(int startRow, int startCol,
                                     const std::vector<ChoiceData>& choicesData) {
    size_t currentRow = 0;

    for (const auto& choice : choicesData) {
        for (size_t lineIdx = 0; lineIdx < choice.lines.size(); ++lineIdx) {
            TerminalUtils::moveCursor(startRow + static_cast<int>(currentRow + lineIdx),
                                     startCol);

            if (lineIdx == 0) {
                // Первая строка варианта с номером
                std::ostringstream number;
                number << std::setw(2) << choice.number << ". ";

                std::cout << TextStyles::styled(number.str(),
                                               TextStyles::Theme::Number,
                                               TextStyles::Style::Bold)
                         << TextStyles::styled(choice.lines[lineIdx],
                                              TextStyles::Theme::Interactive);
            } else {
                // Последующие строки (перенос) с выравниванием
                std::cout << "    "
                         << TextStyles::styled(choice.lines[lineIdx],
                                              TextStyles::Theme::Interactive);
            }
        }
        currentRow += choice.lines.size();
    }
}

// ==================== ПОДСКАЗКА УПРАВЛЕНИЯ ====================

void PanelComponents::drawControlHint(int row, int col, size_t itemCount,
                                     const std::string& action,
                                     bool isImportant) {
    TerminalUtils::moveCursor(row, col);

    TextStyles::Color color = isImportant ?
        TextStyles::Theme::Important : TextStyles::Theme::Hint;

    if (itemCount == 0) {
        std::cout << TextStyles::styled("Нет доступных действий", color);
    } else if (itemCount == 1) {
        std::string text = "Нажмите "
                         + TextStyles::styled("1", TextStyles::Theme::Number,
                                             TextStyles::Style::Bold)
                         + " для " + action;
        std::cout << TextStyles::styled(text, color);
    } else {
        std::string text = "Нажмите "
                         + TextStyles::styled("1-" + std::to_string(itemCount),
                                             TextStyles::Theme::Number,
                                             TextStyles::Style::Bold)
                         + " для " + action;
        std::cout << TextStyles::styled(text, color);
    }
}

// ==================== ПУСТАЯ ПАНЕЛЬ ====================

void PanelComponents::drawEmptyPanel(int row, int col, int width) {
    drawPanelFrame(row, col, EMPTY_PANEL_HEIGHT, width);

    const int textStartCol = col + TITLE_INDENT;

    // Первая строка - заголовок
    TerminalUtils::moveCursor(row + 1, textStartCol);
    std::cout << TextStyles::styled(EMPTY_PANEL_LINES[0],
                                   TextStyles::Theme::Title,
                                   TextStyles::Style::Bold);

    // Остальные строки
    for (size_t i = 1; i < EMPTY_PANEL_LINES.size(); ++i) {
        TerminalUtils::moveCursor(row + static_cast<int>(i) + 1, textStartCol);

        TextStyles::Color color = (i == 3 || i == 4) ?  // Управление и выход
            TextStyles::Theme::Hint : TextStyles::Theme::NormalText;

        std::cout << TextStyles::styled(EMPTY_PANEL_LINES[i], color);
    }
}

// ==================== СПЕЦИАЛИЗИРОВАННЫЕ МЕТОДЫ ====================

void PanelComponents::drawDialogueSpeaker(int row, int col,
                                         const std::string& speakerName) {
    TerminalUtils::moveCursor(row, col);
    std::cout << TextStyles::styled("💬 Диалог с ", TextStyles::Theme::Emoji)
              << TextStyles::styled(speakerName,
                                   TextStyles::Theme::DialogueSpeaker,
                                   TextStyles::Style::Bold);
}

void PanelComponents::drawEmoji(int row, int col, const std::string& emoji) {
    TerminalUtils::moveCursor(row, col);
    std::cout << TextStyles::styled(emoji, TextStyles::Theme::Emoji);
}

void PanelComponents::drawNumber(int row, int col, int number) {
    TerminalUtils::moveCursor(row, col);
    std::cout << TextStyles::styled(std::to_string(number),
                                   TextStyles::Theme::Number,
                                   TextStyles::Style::Bold);
}

void PanelComponents::drawInteractiveItem(int row, int col,
                                         const std::string& name,
                                         const std::string& description,
                                         bool showDescription) {
    TerminalUtils::moveCursor(row, col);

    std::cout << TextStyles::styled(name,
                                   TextStyles::Theme::Interactive,
                                   TextStyles::Style::Bold);

    if (showDescription && !description.empty()) {
        std::cout << " - "
                 << TextStyles::styled(description,
                                      TextStyles::Theme::Description);
    }
}

// ==================== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ====================

TextStyles::Color PanelComponents::getColorForItemType(const Object* item) {
    // Можно расширить для разных типов объектов
    // Например: NPC - синий, Предмет - зелёный, Дверь - жёлтый и т.д.
    return TextStyles::Theme::Interactive;
}

std::string PanelComponents::applyItemStyle(const Object* item,
                                           const std::string& text) {
    return TextStyles::styled(text,
                             getColorForItemType(item),
                             TextStyles::Style::Bold);
}