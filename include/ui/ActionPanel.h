#pragma once
#include "model/Model.h"
#include "ui/ActionPanelLayout.h"
#include "ui/ActionPanelComponents.h"

class ActionPanel {
private:
    Model& model;

    // Основные методы отрисовки панелей
    void drawInteractablesList(int row, int col, int width) const;
    void drawDialogue(int row, int col, int width, const DialogueNode* node) const;
    void drawEmpty(int row, int col, int width) const;

public:
    explicit ActionPanel(Model& model);
    void draw(int row, int col, int width) const;
};