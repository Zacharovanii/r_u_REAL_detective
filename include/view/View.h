#pragma once
#include "model/Model.h"

class View {
public:
    View(const Model& model);
    void draw();

private:
    const Model& model;
};
