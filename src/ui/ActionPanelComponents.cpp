#include "ui/ActionPanelComponents.h"
#include "ui/ActionPanelLayout.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// ==================== CONSTANTS ====================

constexpr int PanelComponents::TITLE_INDENT;
constexpr int PanelComponents::CONTENT_INDENT;
constexpr int PanelComponents::PANEL_PADDING;
constexpr size_t PanelComponents::EMPTY_PANEL_HEIGHT;

constexpr std::array<const char*, 6> PanelComponents::EMPTY_PANEL_LINES;

// ==================== FRAME & TITLE ====================

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
        std::cout << icon << " ";
    }
    std::cout << title;
}

// ==================== TEXT LINES ====================

void PanelComponents::drawTextLines(int startRow, int startCol,
                                   const std::vector<std::string>& lines) {
    for (size_t i = 0; i < lines.size(); ++i) {
        TerminalUtils::moveCursor(startRow + static_cast<int>(i), startCol);
        std::cout << lines[i];
    }
}

// ==================== NUMBERED LIST ====================

void PanelComponents::drawNumberedList(int startRow, int startCol,
                                      const std::vector<const Interactable*>& items,
                                      bool showDescriptions) {
    for (size_t i = 0; i < items.size(); ++i) {
        TerminalUtils::moveCursor(startRow + static_cast<int>(i), startCol);
        
        const auto* item = items[i];
        if (!item) continue;
        
        std::cout << (i + 1) << ". " << item->getName();
        
        // Добавляем описание, если нужно и оно есть
        if (showDescriptions && !item->getDescription().empty()) {
            std::cout << " - " << item->getDescription();
        }
    }
}

// ==================== CHOICES LIST ====================

void PanelComponents::drawChoicesList(int startRow, int startCol,
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

// ==================== CONTROL HINT ====================

void PanelComponents::drawControlHint(int row, int col, size_t itemCount,
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

// ==================== EMPTY PANEL ====================

void PanelComponents::drawEmptyPanel(int row, int col, int width) {
    drawPanelFrame(row, col, EMPTY_PANEL_HEIGHT, width);

    const int textStartCol = col + TITLE_INDENT;
    for (size_t i = 0; i < EMPTY_PANEL_LINES.size(); ++i) {
        TerminalUtils::moveCursor(row + static_cast<int>(i) + 1, textStartCol);
        std::cout << EMPTY_PANEL_LINES[i];
    }
}