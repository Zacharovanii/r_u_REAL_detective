#include "ui/TerminalUtils.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

void TerminalUtils::clearScreen() {
    std::cout << "\033[H\033[2J\033[3J";
}

void TerminalUtils::moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

void TerminalUtils::hideCursor() {
    std::cout << "\033[?25l";
}

void TerminalUtils::showCursor() {
    std::cout << "\033[?25h";
}

void TerminalUtils::getTerminalSize(int &rows, int &cols) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    rows = w.ws_row;
    cols = w.ws_col;
}
