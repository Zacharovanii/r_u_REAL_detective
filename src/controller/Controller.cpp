#include "controller/Controller.h"
#include "ui/TerminalUtils.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>

using namespace std;

struct TermiosGuard {
    termios oldt;
    TermiosGuard() {
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    ~TermiosGuard() {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
};

Controller::Controller(Model &m, View &v) : model(m), view(v) {}

void Controller::run() {
    TermiosGuard guard;
    view.draw();

    char ch;
    while (true) {
        ch = getchar();

        if (ch == '\033') {TerminalUtils::clearScreen(); break;}

        if (ch == 'w') model.moveUp();
        if (ch == 's') model.moveDown();
        if (ch == 'a') model.moveLeft();
        if (ch == 'd') model.moveRight();

        model.update();

        view.draw();
    }
}
