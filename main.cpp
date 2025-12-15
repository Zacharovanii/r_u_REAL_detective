#include "model/Model.h"
#include "view/View.h"
#include "controller/Controller.h"
#include "model/GameState.h"

int main() {
    do {
        Model model;
        View view(model);
        Controller controller(model, view);

        controller.run();
    } while (State::needRestart());

    return 0;
}
