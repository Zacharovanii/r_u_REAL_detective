#include "model/Model.h"
#include "view/View.h"
#include "controller/Controller.h"

int main() {
    Model model;
    View view(model);
    Controller controller(model, view);

    controller.run();
    return 0;
}
