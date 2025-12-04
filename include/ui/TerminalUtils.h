#pragma once
#include "helpers/Platform.h"
#include <iostream>

class TerminalUtils {
public:
    static void clearScreen();
    static void moveCursor(size_t row, size_t col);
    static void hideCursor();
    static void showCursor();
    static void getTerminalSize(size_t &rows, size_t &cols);

    static char readChar();

    static void init();
};