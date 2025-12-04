#pragma once
#include <string>
#include <vector>
#include "model/objects/Interactable.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include "ui/ActionPanelLayout.h"

class PanelComponents {
public:
    static void drawPanelFrame(int row, int col, size_t height, int width, 
                              const std::string& title = "");
    
    static void drawTitle(int row, int col, const std::string& title, 
                         const std::string& icon = "");
    
    static void drawTextLines(int startRow, int startCol, 
                             const std::vector<std::string>& lines);
    
    static void drawNumberedList(int startRow, int startCol,
                                const std::vector<const Interactable*>& items,
                                bool showDescriptions);
    
    static void drawChoicesList(int startRow, int startCol,
                               const std::vector<ChoiceData>& choicesData);
    
    static void drawControlHint(int row, int col, size_t itemCount,
                               const std::string& action = "взаимодействия");
    
    static void drawEmptyPanel(int row, int col, int width);
    
private:
    static constexpr int TITLE_INDENT = 2;
    static constexpr int CONTENT_INDENT = 4;
    static constexpr int PANEL_PADDING = 2;
    static constexpr size_t EMPTY_PANEL_HEIGHT = 8;
    
    static constexpr std::array<const char*, 6> EMPTY_PANEL_LINES = {
        "Действия:", "Подойдите к персонажу или предмету",
        "для начала взаимодействия", "Управление: WASD",
        "Выход: ESC", "(Ваш прогресс не сохраняется)"
    };
};