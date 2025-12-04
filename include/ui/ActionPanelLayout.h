#pragma once
#include "model/dialogue/Dialogue.h"
#include "helpers/TextWrapper.h"
#include <vector>
#include <string>

struct ChoiceData {
    size_t number;
    std::vector<std::string> lines;
};

struct DialogueLayout {
    std::vector<std::string> textLines;
    std::vector<ChoiceData> choicesData;
    size_t totalHeight;
};

struct PanelMetrics {
    size_t height;
    size_t itemsCount;
    bool showDescriptions;
};

class ActionPanelLayout {
public:
    static PanelMetrics calculateInteractablesLayout(size_t itemCount);
    static DialogueLayout calculateDialogueLayout(const DialogueNode* node, int availableWidth);
    
    static bool shouldShowDescription(int width) {
        return width > MIN_WIDTH_FOR_DESCRIPTION;
    }
    
private:
    static constexpr int MIN_WIDTH_FOR_DESCRIPTION = 30;
};