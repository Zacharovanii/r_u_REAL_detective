#pragma once
#include "model/Model.h"
#include "model/dialogue/Dialogue.h"
#include <vector>
#include <string>

class ActionPanel {
private:
    const Model& model;

    static constexpr int EMPTY_PANEL_LINES_COUNT = 6;
    static constexpr const char* EMPTY_PANEL_TEXT[EMPTY_PANEL_LINES_COUNT] = {
        "Действия:",
        "Подойдите к персонажу или предмету",
        "для начала взаимодействия",
        "Управление: WASD",
        "Выход: ESC",
        "(Ваш прогресс не сохраняется)"
    };

public:
    explicit ActionPanel(const Model& model);

    void draw(int row, int col, int width) const;
    static void drawDialogue(int row, int col, int width, const DialogueNode* node);

    static std::vector<std::string> wrapText(const std::string& text, int max_width);
    static int getStringWidth(const std::string& str);


    void drawInteractablesList(int row, int col, int width) const;
    static void drawEmpty(int row, int col, int width);
};