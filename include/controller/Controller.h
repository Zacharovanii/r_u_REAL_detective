#pragma once
#include <optional>
#include "model/Model.h"
#include "view/View.h"

class Controller {
private:
    Model &model;
    View &view;

    void handleExplorationInput(char ch) const;
    void handleDialogueInput(size_t choice) const;
    void handleInteractionChoice(size_t ch) const;

    [[nodiscard]] static std::optional<size_t> charToIndex(char ch);

public:
    Controller(Model &m, View &v);

    void run() const;
};
