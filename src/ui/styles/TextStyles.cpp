#include "ui/styles/TextStyles.h"

std::string StyledText::getText() const { return text; }
void StyledText::setText(const std::string& newText) { text = newText; }

std::string StyledText::getStyledText() const {
    std::string result;

    if (color != Color::Default)
        result += "\033[" + std::to_string(static_cast<int>(color)) + "m";
    if (background != Background::Default)
        result += "\033[" + std::to_string(static_cast<int>(background)) + "m";
    if (style != Style::Reset)
        result += "\033[" + std::to_string(static_cast<int>(style)) + "m";

    result += text + "\033[0m";
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