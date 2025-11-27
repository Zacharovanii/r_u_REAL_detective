#include "src/model/Model.h"
#include "src/view/View.h"
#include "src/controller/Controller.h"

int main() {
    Model model;
    View view(model);
    Controller controller(model, view);

    controller.run();
    return 0;
}
