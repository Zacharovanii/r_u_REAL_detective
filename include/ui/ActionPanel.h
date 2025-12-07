#pragma once
#include "model/Model.h"
#include "helpers/Types.h"
#include "ui/styles/TextStyles.h"

class ActionPanel {
private:
    Model& model;
    std::string about[6] = {
        TextStyles::styled("Действия:", Color::Blue),
        "Подойдите к персонажу или предмету",
        "для начала взаимодействия",
        "Управление: WASD",
        "Выход: ESC",
        "(Ваш прогресс не сохраняется)"
    };

    void drawDialogue(PanelMetrics pm) const;
    void drawNearbyItems(PanelMetrics pm) const;
    void drawEmpty(const PanelMetrics& pm) const;
public:
    explicit ActionPanel(Model& model);
    void draw(const PanelMetrics& pm) const;
};