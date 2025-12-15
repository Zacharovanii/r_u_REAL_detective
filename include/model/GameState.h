#pragma once

namespace State {
    extern bool restart;
    extern bool quit;

    void requestRestart();
    void requestQuit();

    bool needRestart();
    bool needQuit();

    void reset();
}