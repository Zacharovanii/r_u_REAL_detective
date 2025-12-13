#pragma once
#include "model/Model.h"
#include "helpers/Types.h"

class MapRenderer {
public:
    explicit MapRenderer(Model& model);
    void draw(const PanelMetrics& pm, int radiusY, int radiusX) const;

private:
    Model& model;

    void drawAreaAroundPlayer(const PanelMetrics& pm, int radiusY, int radiusX) const;
    void drawTile(int dy, int dx) const;
    [[nodiscard]] bool isValidPosition(int y, int x) const;
};
