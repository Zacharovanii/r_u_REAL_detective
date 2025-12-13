#pragma once
#include "model/Model.h"
#include "ui/ActionPanel.h"
#include "ui/MapRenderer.h"
#include "ui/StatusPanel.h"

class View {
public:
    explicit View(Model& model);
    ~View();

    void draw() const;

private:
    Model& model;
    StatusPanel statusPanel;
    MapRenderer mapRenderer;
    ActionPanel actionPanel;
};
