#pragma once
#include "model/Model.h"

class MapRenderer {
public:
    void draw(const Model& model, int row, int col, int radius = 1);

private:
    void drawAreaAroundPlayer(const Model& model, int row, int col, int radius);
};
