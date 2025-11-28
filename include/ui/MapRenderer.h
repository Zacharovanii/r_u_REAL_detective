#pragma once
#include "model/Model.h"

class MapRenderer {
public:
    explicit MapRenderer(const Model& model);

    void draw(int row, int col, int radiusY, int radiusX) const;
    void draw(int row, int col, int radius) const;

private:
    const Model& model;

    void drawTile(int row, int col, int radiusY, int radiusX, int dy, int dx) const;
    void drawAreaAroundPlayer(int row, int col, int radiusY, int radiusX) const;
    [[nodiscard]] bool isValidPosition(int y, int x) const;
};
