#pragma once
#include "helpers/Platform.h"
#include <iostream>


class TerminalUtils {
public:
    static void clearScreen();
    static void moveCursor(int row, int col);
    static void hideCursor();
    static void showCursor();
    static void getTerminalSize(int &rows, int &cols);

    static char readChar();

    static void init();

private:
#if PLATFORM_WINDOWS
    static void initWindowsConsole();
    static void restoreWindowsConsole();
#else
    static void initPosixTerminal();
    static void restorePosixTerminal();
#endif
    static bool initialized;
};