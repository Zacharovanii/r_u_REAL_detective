#pragma once
#include "model/Model.h"
#include "model/dialogue/Dialogue.h"
#include <vector>
#include <string>
#include <array>

class TextWrapper;

struct ChoiceData {
    size_t number;
    std::vector<std::string> lines;
};

struct DialogueLayout {
    std::vector<std::string> textLines;
    std::vector<ChoiceData> choicesData;
    size_t totalHeight;
};

class ActionPanel {
private:
    const Model& model;

    // Константы
    static constexpr int PANEL_PADDING = 2;
    static constexpr int TITLE_INDENT = 2;
    static constexpr int CONTENT_INDENT = 4;
    static constexpr int MIN_WIDTH_FOR_DESCRIPTION = 30;
    static constexpr size_t EMPTY_PANEL_HEIGHT = 8;

    static constexpr std::array<const char*, 6> EMPTY_PANEL_LINES = {
        "Действия:",
        "Подойдите к персонажу или предмету",
        "для начала взаимодействия",
        "Управление: WASD",
        "Выход: ESC",
        "(Ваш прогресс не сохраняется)"
    };

    // Методы расчёта размеров
    static size_t calculateInteractablesHeight(size_t itemCount);
    static DialogueLayout calculateDialogueLayout(const DialogueNode* node, int availableWidth);

    // Методы отрисовки отдельных компонентов
    static void drawPanelFrame(int row, int col, size_t height, int width,
                              const std::string& title = "");

    static void drawTitle(int row, int col, const std::string& title,
                         const std::string& icon = "");

    static void drawTextLines(int startRow, int startCol,
                             const std::vector<std::string>& lines);

    static void drawNumberedList(int startRow, int startCol,
                                const std::vector<const Interactable*>& items,
                                int availableWidth);

    static void drawChoicesList(int startRow, int startCol,
                               const std::vector<ChoiceData>& choicesData);

    static void drawControlHint(int row, int col, size_t itemCount,
                               const std::string& action = "взаимодействия");

    // Основные методы отрисовки панелей
    void drawInteractablesList(int row, int col, int width) const;
    static void drawDialogue(int row, int col, int width, const DialogueNode* node);
    static void drawEmpty(int row, int col, int width);

public:
    explicit ActionPanel(const Model& model);
    void draw(int row, int col, int width) const;

    static bool shouldShowDescription(int width) {
        return width > MIN_WIDTH_FOR_DESCRIPTION;
    }
};