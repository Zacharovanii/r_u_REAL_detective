#pragma once
#include "model/Model.h"
#include "ui/ActionPanel.h"
#include "ui/MapRenderer.h"

class View {
public:
    explicit View(const Model& model);
    ~View();

    void draw() const;

private:
    const Model& model;
    MapRenderer mapRenderer;
    ActionPanel actionPanel;
};
