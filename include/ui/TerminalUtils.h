#pragma once

class TerminalUtils {
public:
    static void clearScreen();
    static void moveCursor(int row, int col);
    static void hideCursor();
    static void showCursor();
    static void getTerminalSize(int &rows, int &cols);
};
