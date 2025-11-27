#include "View.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

View::View(const Model& m) : model(m) {}
View::~View() {
    showCursor();
}

void View::clearScreen() const {
    cout << "\033[H\033[2J\033[3J";
}

void View::moveCursor(int row, int col) const {
    cout << "\033[" << row << ";" << col << "H";
}

void View::hideCursor() const {
    cout << "\033[?25l";
}

void View::showCursor() const {
    cout << "\033[?25h";
}

void View::getTerminalSize(int &rows, int &cols) const {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    rows = w.ws_row;
    cols = w.ws_col;
}

void View::drawFrame(int startRow, int startCol, int height, int width) const {
    // Рамка Unicode
    const char* TL = "┌";
    const char* TR = "┐";
    const char* BL = "└";
    const char* BR = "┘";
    const char* H  = "─";
    const char* V  = "│";

    // Верхняя линия
    moveCursor(startRow, startCol);
    cout << TL;
    for (int i = 0; i < width - 2; i++) cout << H;
    cout << TR;

    // Бока
    for (int r = 1; r < height - 1; r++) {
        moveCursor(startRow + r, startCol);
        cout << V;
        moveCursor(startRow + r, startCol + width - 1);
        cout << V;
    }

    // Нижняя линия
    moveCursor(startRow + height - 1, startCol);
    cout << BL;
    for (int i = 0; i < width - 2; i++) cout << H;
    cout << BR;
}



void View::drawStatus() const {
    const Model::Player &p = model.getPlayer();

    moveCursor(1, 1);
    cout << "=== Игрок ===\n";
    cout << "Позиция: (" << p.x << "," << p.y << ")\n";
    cout << "HP: " << p.hp << "\n";
    cout << "Статус: " << p.status << "\n";
}

void View::drawAction() const {
    int termRows, termCols;
    getTerminalSize(termRows, termCols);

    string t1 = "=== Диалог / Взаимодействие ===\n";
    string t2 = "(здесь будет окно диалога)";

    int half1 = t1.length() / 4;
    int half2 = t2.length() / 4;

    int startCol = termCols / 2;
    int startCol1 = startCol - half1;
    int startCol2 = startCol - half2;


    moveCursor(1, startCol1);
    cout << t1;
    moveCursor(2, startCol2);
    cout << t2;
}

void View::drawMap() const {
    int termRows, termCols;
    getTerminalSize(termRows, termCols);

    const auto &m = model.getMap();
    const auto &p = model.getPlayer();

    int startCol = termCols - m[0].size() - 5;
    int startRow = 1;

    for (int r = 0; r < m.size(); r++) {
        moveCursor(startRow + r, startCol);

        for (int c = 0; c < m[0].size(); c++) {
            if (r == p.y && c == p.x) cout << "@";
            else cout << m[r][c];
        }
    }

    hideCursor();
}

void View::draw() const {
    clearScreen();
    drawStatus();
    drawAction();
    drawMap();
    cout.flush();
}
