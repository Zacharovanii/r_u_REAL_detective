#include "helpers/TermiosGuard.h"
#include "controller/Controller.h"
#include "ui/TerminalUtils.h"
#include "helpers/Types.h"
#include "model/GameState.h"

Controller::Controller(
    Model &m, View &v
):
    model(m), view(v)
{
    State::reset();
}

void Controller::run() const {
    TerminalGuard guard;
    TerminalUtils::init();
    view.draw();

    constexpr char ESC = '\033';
    char ch;
    bool isInDialogue;
    bool isChoice;

    do {
        ch = TerminalUtils::readChar();
        isInDialogue = model.isInDialogue();
        isChoice = ch >= '1' && ch <= '9';

        if (ch == ESC)
            break;
        else if (isInDialogue && isChoice) {
            handleDialogueInput(charToIndex(ch));
            if (State::needRestart()) break;
            else if (State::needQuit()) break;
        }
        else if (isChoice)
            handleInteractionChoice(charToIndex(ch));
        else
            handleExplorationInput(ch);

        if (ch) {
            model.update();
            view.draw();
        }
    }
    while (ch != ESC);
    TerminalUtils::clearScreen();
}

size_t Controller::charToIndex(char ch) {
    return static_cast<size_t>(ch - '1'); // преобразуем '1' в 0, '2' в 1 и т.д
}

void Controller::handleExplorationInput(char ch) const {
    switch (ch) {
        case 'w': model.movePlayer(Direction::UP); break;
        case 's': model.movePlayer(Direction::DOWN); break;
        case 'a': model.movePlayer(Direction::LEFT); break;
        case 'd': model.movePlayer(Direction::RIGHT); break;
        default: break;
    }
}

void Controller::handleInteractionChoice(size_t index) const {
    model.interactWithNearby(index);
}

void Controller::handleDialogueInput(size_t choice) const {
    model.makeChoice(choice);
}