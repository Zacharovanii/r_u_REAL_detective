#pragma once
#include "model/Model.h"
#include "model/Dialogue.h"

class ActionPanel {
private:
    const Model& model;
public:
    explicit ActionPanel(const Model& model);

    void draw(int row, int col, int width) const;
    void drawDialogue(int row, int col, int width, const class Dialogue* dialogue) const;
    void drawEmpty(int row, int col, int width) const;
};