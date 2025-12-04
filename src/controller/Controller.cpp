#include "helpers/TermiosGuard.h"
#include "controller/Controller.h"
#include "ui/TerminalUtils.h"
#include "helpers/Types.h"


Controller::Controller(Model &m, View &v) :
                        model(m), view(v)
{}

void Controller::run() const {
    TerminalGuard guard;
    TerminalUtils::init();
    view.draw();

    constexpr char ESC = '\033';
    char ch;

    do {
        ch = TerminalUtils::readChar();
        bool isInDialogue = model.getDialogueManager().isInDialogue();


        if (ch == ESC) {
            break;
        } else if (isInDialogue) {
            if (ch == 'q') model.getDialogueManager().endDialogue();
            else if (auto choice = charToIndex(ch)) {
                handleDialogueInput(choice.value());
            }
        } else if (auto choice = charToIndex(ch)) {
            handleInteractionChoice(choice.value());
        } else {
            handleExplorationInput(ch);
        }

        if (ch) {
            model.update();
            view.draw();
        }
    }
    while (ch != ESC);

    TerminalUtils::clearScreen();
}

std::optional<size_t> Controller::charToIndex(char ch) const {
    if (ch >= '1' && ch <= '9')  return static_cast<size_t>(ch - '1'); // преобразуем '1' в 0, '2' в 1 и т.д
    return std::nullopt;
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
    model.getDialogueManager().makeChoice(choice);
}