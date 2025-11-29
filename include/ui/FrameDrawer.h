#pragma once
#include <string>

class FrameDrawer {
public:
    static void drawFrame(int row, int col, int height, int width);
    static void drawFrame(int row, int col, int height, int width, const std::string& title);
};