#pragma once
#include "../model/Model.h"
#include <string>

class View {
    const Model& model;

public:
    View(const Model& m);
    ~View();

    void clearScreen() const;
    void moveCursor(int row, int col) const;
    void hideCursor() const;
    void showCursor() const;

    void draw() const;

private:
    void drawStatus() const;
    void drawAction() const;
    void drawMap() const;

    void getTerminalSize(int &rows, int &cols) const;
    void drawFrame(int startRow, int startCol, int height, int width) const;
};
