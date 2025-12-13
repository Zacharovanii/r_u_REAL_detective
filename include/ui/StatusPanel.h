#pragma once
#include "model/Model.h"
#include "helpers/Types.h"

class StatusPanel {
private:
    Model& model;
public:
    explicit StatusPanel(Model& model);
    // void draw(int row, int col, int width) const;
    void draw(const PanelMetrics& pm) const;
};
