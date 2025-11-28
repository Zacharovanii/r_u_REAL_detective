#pragma once
#include "model/Model.h"
#include "ui/MapRenderer.h"

class View {
public:
    View(const Model& model);
    void draw();

private:
    const Model& model;
    MapRenderer mapRenderer = MapRenderer();
};
