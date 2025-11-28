#pragma once
#include "model/Model.h"
#include "ui/MapRenderer.h"

class View {
public:
    explicit View(const Model& model);
    ~View();

    void draw() const;
    // void drawCompactLayout(int cols) const;

private:
    const Model& model;
    MapRenderer mapRenderer;
};
