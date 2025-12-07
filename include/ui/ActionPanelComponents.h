#pragma once
#include <string>
#include <vector>
#include <array>
#include "model/objects/Object.h"
#include "ui/FrameDrawer.h"
#include "ui/TerminalUtils.h"
#include "ui/styles/TextStyles.h"
#include "ui/ActionPanelLayout.h"
#include "model/objects/Interactable.h"

class PanelComponents {
public:
    // Инициализация стилей
    static void initStyles();

    // Основные методы отрисовки
    static void drawPanelFrame(int row, int col, size_t height, int width,
                              const std::string& title = "");

    static void drawTitle(int row, int col, const std::string& title,
                         const std::string& icon = "");

    static void drawTextLines(int startRow, int startCol,
                             const std::vector<std::string>& lines,
                             TextStyles::Color color = TextStyles::Theme::NormalText,
                             TextStyles::Style style = TextStyles::Style::Normal);

    static void drawNumberedList(int startRow, int startCol,
                                const std::vector<Interactable*>& items,
                                bool showDescriptions);

    static void drawChoicesList(int startRow, int startCol,
                               const std::vector<ChoiceData>& choicesData);

    static void drawControlHint(int row, int col, size_t itemCount,
                               const std::string& action = "взаимодействия",
                               bool isImportant = false);

    static void drawEmptyPanel(int row, int col, int width);

    // Специализированные методы для конкретных элементов
    static void drawDialogueSpeaker(int row, int col, const std::string& speakerName);
    static void drawEmoji(int row, int col, const std::string& emoji);
    static void drawNumber(int row, int col, int number);
    static void drawInteractiveItem(int row, int col, const std::string& name,
                                   const std::string& description = "",
                                   bool showDescription = true);

private:
    // Константы отступов
    static constexpr int TITLE_INDENT = 2;
    static constexpr int CONTENT_INDENT = 4;
    static constexpr int PANEL_PADDING = 2;
    static constexpr size_t EMPTY_PANEL_HEIGHT = 8;

    // Текст пустой панели
    static constexpr std::array<const char*, 6> EMPTY_PANEL_LINES = {
        "Действия:", "Подойдите к персонажу или предмету",
        "для начала взаимодействия", "Управление: WASD",
        "Выход: ESC", "(Ваш прогресс не сохраняется)"
    };

    // Стили для разных типов текста
    static TextStyles::Color getColorForItemType(const Object* item);
    static std::string applyItemStyle(const Object* item,
                                     const std::string& text);
};