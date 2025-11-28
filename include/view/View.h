#pragma once
#include "model/Model.h"

class View {
public:
    explicit View(const Model& model);
    ~View();
    void draw() const;

private:
    const Model& model;
};
