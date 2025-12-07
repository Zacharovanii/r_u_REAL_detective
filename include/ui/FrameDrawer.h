#pragma once
#include <string>
#include "helpers/Types.h"
#include "styles/TextStyles.h"

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
    static void drawFrame(PanelMetrics pm);
    static void drawTitle(PanelMetrics pm, const std::string& title);
    static void drawTitle(PanelMetrics pm, const StyledText& title);
    static void drawHint(PanelMetrics pm, const std::string& hint);

    static void drawFrameWithTitle(PanelMetrics pm, const std::string& title);
    static void drawFrameWithTitle(PanelMetrics pm, const StyledText& title);
    static void drawFrameWithHint(PanelMetrics pm, const std::string& hint);
    static void drawFrameWithTitleAndHint(PanelMetrics pm, const std::string& title, const std::string& hint);
};
