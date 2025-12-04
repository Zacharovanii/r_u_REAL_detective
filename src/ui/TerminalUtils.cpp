#include "ui/TerminalUtils.h"
#include <iostream>
#include <chrono>


void TerminalUtils::init() {
#if PLATFORM_WINDOWS
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

void TerminalUtils::clearScreen() {
#if PLATFORM_WINDOWS
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hStdOut, ' ', cellCount, coord, &count);
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);
#else
    std::cout << "\033[H\033[2J\033[3J";
#endif
}

void TerminalUtils::moveCursor(size_t row, size_t col) {
#if PLATFORM_WINDOWS
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {static_cast<SHORT>(col - 1), static_cast<SHORT>(row - 1)};
    SetConsoleCursorPosition(hStdOut, coord);
#else
    std::cout << "\033[" << row << ";" << col << "H";
#endif
}

void TerminalUtils::hideCursor() {
#if PLATFORM_WINDOWS
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hStdOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &cursorInfo);
#else
    std::cout << "\033[?25l";
#endif
}

void TerminalUtils::showCursor() {
#if PLATFORM_WINDOWS
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hStdOut, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hStdOut, &cursorInfo);
#else
    std::cout << "\033[?25h";
#endif
}

void TerminalUtils::getTerminalSize(size_t &rows, size_t &cols) {
#if PLATFORM_WINDOWS
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    rows = w.ws_row;
    cols = w.ws_col;
#endif
}

char TerminalUtils::readChar() {
#if PLATFORM_WINDOWS
    return _getwch();
#else
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
#endif
}