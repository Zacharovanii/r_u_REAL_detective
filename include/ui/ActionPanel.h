#pragma once
#include "model/Model.h"
#include "helpers/Types.h"
#include "ui/styles/TextStyles.h"

class ActionPanel {
private:
    Model& model;
    std::string about[6];

    void drawDialogue(const PanelMetrics& pm) const;
    void drawNearbyItems(const PanelMetrics& pm) const;
    void drawEmpty(const PanelMetrics& pm) const;
public:
    explicit ActionPanel(Model& model);
    void draw(const PanelMetrics& pm) const;
};