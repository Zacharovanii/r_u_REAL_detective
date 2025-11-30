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

    while (true) {
        char ch = getchar();

        if (ch == '\033') {
            if (model.getDialogueManager().isInDialogue()) {
                model.getDialogueManager().endDialogue();
            } else {
                break;
            }
        }
            // Отладочные команды
        else if (ch == 't' || ch == 'T') {
            // cout << "ACTION: DEBUG - Starting dialogue" << endl;
            model.getDialogueManager().startDialogue("robert_dialogue");
        }
        else if (ch == 'y' || ch == 'Y') {
            // cout << "ACTION: DEBUG - Ending dialogue" << endl;
            model.getDialogueManager().endDialogue();
        }
            // Цифры в диалоге
        else if (ch >= '1' && ch <= '9') {
            if (model.getDialogueManager().isInDialogue()) {
                size_t choice = ch - '1';
                // cout << "ACTION: Making dialogue choice " << choice << endl;
                model.getDialogueManager().makeChoice(choice);
            } else {
                // cout << "ACTION: Ignoring number (not in dialogue)" << endl;
            }
        }
            // Движение вне диалога
        else if (!model.getDialogueManager().isInDialogue()) {
            handleExplorationInput(ch);
        }

        model.update();
        if (ch)
        {
            view.draw();
        }
    }

    TerminalUtils::clearScreen();
    cout << "=== GAME ENDED ===" << endl;
}

bool Controller::isKeyPressed() {
    fd_set readfds;
    struct timeval tv = {0, 0};
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    return select(1, &readfds, NULL, NULL, &tv) > 0;
}

void Controller::handleExplorationInput(char ch) {
    switch (ch) {
        case 'w': model.moveUp(); break;
        case 's': model.moveDown(); break;
        case 'a': model.moveLeft(); break;
        case 'd': model.moveRight(); break;
    }
}

void Controller::handleDialogueInput(char ch) {
    // Обработка выбора в диалоге
    if (ch >= '1' && ch <= '9') {
        size_t choice_index = ch - '1'; // преобразуем '1' в 0, '2' в 1 и т.д.
        model.getDialogueManager().makeChoice(choice_index);
    }
}