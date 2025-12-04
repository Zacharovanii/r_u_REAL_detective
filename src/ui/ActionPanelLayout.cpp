#include "ui/ActionPanelLayout.h"
#include <algorithm>

// ==================== INTERACTABLES LAYOUT ====================
PanelMetrics ActionPanelLayout::calculateInteractablesLayout(size_t itemCount) {
    PanelMetrics metrics;
    metrics.itemsCount = itemCount;
    
    // Минимальная высота = заголовок + подсказка + хотя бы 1 элемент
    constexpr size_t minHeight = 8;
    const size_t calculatedHeight = 3 + itemCount; // заголовок + элементы + подсказка
    
    metrics.height = std::max(calculatedHeight, minHeight);
    return metrics;
}

// ==================== DIALOGUE LAYOUT ====================

DialogueLayout ActionPanelLayout::calculateDialogueLayout(const DialogueNode* node, 
                                                         int availableWidth) {
    DialogueLayout layout;
    
    if (!node || availableWidth <= 0) {
        layout.totalHeight = 8; // минимальная высота пустой панели
        return layout;
    }
    
    const int textMaxWidth = availableWidth - 4; // PANEL_PADDING * 2
    layout.textLines = TextWrapper::wrap(node->text, textMaxWidth);

    // Рассчитываем варианты ответов
    const int choiceMaxWidth = textMaxWidth - 2; // дополнительный отступ для номеров
    for (size_t i = 0; i < node->choices.size(); ++i) {
        auto lines = TextWrapper::wrap(node->choices[i].text, choiceMaxWidth);
        layout.choicesData.push_back({i + 1, std::move(lines)});
    }

    // Рассчитываем общую высоту
    size_t textHeight = layout.textLines.size();
    size_t choicesHeight = 0;
    for (const auto& choice : layout.choicesData) {
        choicesHeight += choice.lines.size();
    }

    layout.totalHeight = 8 + textHeight + choicesHeight; // базово 8 строк
    return layout;
}