#include "ui/styles/TextStyles.h"

static void appendAnsiParam(std::string& result, const std::string& value) {
    if (!result.empty() && result.back() != '[') {
        result += ';';
    }
    result += value;
}

std::string StyledText::getText() const { return text; }
void StyledText::setText(const std::string& newText) { text = newText; }

std::string StyledText::getStyledText() const {
    const bool hasStyles =
        color      != Color::Default ||
        background != Background::Default ||
        style      != Style::Reset;

    if (!hasStyles)
        return text;

    int stl = static_cast<int>(style);
    int clr = static_cast<int>(color);
    int bck = static_cast<int>(background);

    std::string result = "\033[";

    if (style != Style::Reset)
        appendAnsiParam(
            result,
            std::to_string(stl)
            );
    if (color != Color::Default)
        appendAnsiParam(
            result,
            "38;5;" + std::to_string(clr)
            );
    if (background != Background::Default)
        appendAnsiParam(
            result,
            "48;5;" + std::to_string(bck)
            );

    result += 'm';
    result += text;
    result += "\033[0m";

    return result;
}

void StyledText::setColor(Color newColor) { color = newColor; }
void StyledText::setStyle(Style newStyle) { style = newStyle; }
void StyledText::setBackground(Background newBackground) { background = newBackground; }

void StyledText::resetStyles() {
    color = Color::Default;
    style = Style::Reset;
    background = Background::Default;
}