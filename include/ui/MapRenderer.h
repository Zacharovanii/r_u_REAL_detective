#pragma once
#include "model/Model.h"

class MapRenderer {
public:
    static void draw(const Model& model, int row, int col, int radius = 1);

private:
    static void drawAreaAroundPlayer(const Model& model, int row, int col, int radius);
};
