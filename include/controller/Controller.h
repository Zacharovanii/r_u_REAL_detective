#pragma once
#include "model/Model.h"
#include "view/View.h"

class Controller {
    Model &model;
    View &view;

public:
    Controller(Model &m, View &v);

    void run();
    void handleExplorationInput(char ch);
    void handleDialogueInput(char ch);
    bool isKeyPressed();
};
