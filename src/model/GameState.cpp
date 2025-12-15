#include "model/GameState.h"

namespace State {
    bool restart = false;
    bool quit = false;

    void requestRestart() {restart = true;}
    void requestQuit() {quit = true;}

    bool needRestart() {return restart;}
    bool needQuit() {return quit;}

    void reset() {
        restart = false;
        quit = false;
    }
}