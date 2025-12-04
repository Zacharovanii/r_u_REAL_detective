#pragma once
#include <string>

class FrameDrawer {
private:
    inline static const char* TL = "┌";
    inline static const char* TR = "┐";
    inline static const char* BL = "└";
    inline static const char* BR = "┘";
    inline static const char* H  = "─";
    inline static const char* V  = "│";

public:
    static void drawFrame(size_t row, size_t col, size_t height, size_t width);
    static void drawFrame(size_t row, size_t col, size_t height, size_t width, const std::string& title);
};