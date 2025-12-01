#pragma once
#include "model/Model.h"
#include "model/dialogue/Dialogue.h"
#include <vector>
#include <string>

class ActionPanel {
private:
    const Model& model;
public:
    explicit ActionPanel(const Model& model);

    void draw(int row, int col, int width) const;
    void drawDialogue(int row, int col, int width, const class Dialogue* dialogue) const;
    std::vector<std::string> wrapText(const std::string& text, int max_width) const;
    int getStringWidth(const std::string& str) const;
    void drawEmpty(int row, int col, int width) const;
};