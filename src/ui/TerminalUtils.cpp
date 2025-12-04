#include "ui/TerminalUtils.h"
#include <iostream>
#include <chrono>

bool TerminalUtils::initialized = false;

void TerminalUtils::initWindowsConsole() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void TerminalUtils::init() {
#ifdef PLATFORM_WINDOWS
    initWindowsConsole();
#else
    initPosixTerminal();
#endif
}

// --- Общие методы (одинаковые для всех платформ) ---
void TerminalUtils::clearScreen() {
#if PLATFORM_WINDOWS
    // Windows
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
    // Linux/macOS
    std::cout << "\033[H\033[2J\033[3J";
#endif
}

void TerminalUtils::moveCursor(int row, int col) {
#if PLATFORM_WINDOWS
    // Windows
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {static_cast<SHORT>(col - 1), static_cast<SHORT>(row - 1)};
    SetConsoleCursorPosition(hStdOut, coord);
#else
    // Linux/macOS
    std::cout << "\033[" << row << ";" << col << "H";
#endif
}

void TerminalUtils::hideCursor() {
#if PLATFORM_WINDOWS
    // Windows
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hStdOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &cursorInfo);
#else
    // Linux/macOS
    std::cout << "\033[?25l";
#endif
}

void TerminalUtils::showCursor() {
#if PLATFORM_WINDOWS
    // Windows
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hStdOut, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hStdOut, &cursorInfo);
#else
    // Linux/macOS
    std::cout << "\033[?25h";
#endif
}

void TerminalUtils::getTerminalSize(int &rows, int &cols) {
#if PLATFORM_WINDOWS
    // Windows
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    // Linux/macOS
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    rows = w.ws_row;
    cols = w.ws_col;
#endif
}

char TerminalUtils::readChar() {
#if PLATFORM_WINDOWS
    // Windows
    return _getwch();
#else
    // Linux/macOS
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
#endif
}