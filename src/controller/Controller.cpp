#include "controller/Controller.h"
#include "ui/TerminalUtils.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>

using namespace std;

struct TermiosGuard {
    termios old_terminal;
    TermiosGuard() {
        tcgetattr(STDIN_FILENO, &old_terminal);
        termios newt = old_terminal;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    ~TermiosGuard() {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);
    }
};

Controller::Controller(Model &m, View &v) : model(m), view(v) {}

void Controller::run() const {
    TermiosGuard guard;
    view.draw();

    constexpr char ESC = '\033';
    char ch;

    do {
        ch = getchar();
        bool isInDialogue = model.getDialogueManager().isInDialogue();


        if (ch == ESC) {
            break;
        } else if (isInDialogue) {

            if (ch == 'q') model.getDialogueManager().endDialogue();
            else if (ch >= '1' && ch <= '9') handleDialogueInput(ch);
        }
        else handleExplorationInput(ch);


        model.update();
        if (ch) view.draw();
    }
    while (ch != ESC);

    TerminalUtils::clearScreen();
}

void Controller::handleExplorationInput(char ch) const {
    switch (ch) {
        case 'w': model.moveUp(); break;
        case 's': model.moveDown(); break;
        case 'a': model.moveLeft(); break;
        case 'd': model.moveRight(); break;
        default: break;
    }
}

void Controller::handleDialogueInput(char ch) const {
        size_t choice = ch - '1'; // преобразуем '1' в 0, '2' в 1 и т.д.
        model.getDialogueManager().makeChoice(choice);
}