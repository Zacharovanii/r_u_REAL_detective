#pragma once
#include <string>

enum class Color {
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,

    BrightBlack = 90,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93,
    BrightBlue = 94,
    BrightMagenta = 95,
    BrightCyan = 96,
    BrightWhite = 97,

    Default = 39
};

enum class Style {
    Reset = 0,
    Bold = 1,
    Dim = 2,
    Italic = 3,
    Underline = 4,
    Blink = 5,
    Reverse = 7,
    Hidden = 8,
    Strikethrough = 9
};

enum class Background {
    Black = 40,
    Red = 41,
    Green = 42,
    Yellow = 43,
    Blue = 44,
    Magenta = 45,
    Cyan = 46,
    White = 47,

    BrightBlack = 100,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103,
    BrightBlue = 104,
    BrightMagenta = 105,
    BrightCyan = 106,
    BrightWhite = 107,

    Default = 49
};

struct StyledText {
    std::string text;
    Color color = Color::Default;
    Style style = Style::Reset;
    Background background = Background::Default;

    std::string getText() const { return text; }
    void setText(const std::string& newText) { text = newText; }

    std::string getStyledText() const {
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
    void setColor(Color newColor) { color = newColor; }
    void setStyle(Style newStyle) { style = newStyle; }
    void setBackground(Background newBackground) { background = newBackground; }

    void resetStyles() {
        color = Color::Default;
        style = Style::Reset;
        background = Background::Default;
    }
};

namespace TextStyles {
    std::string reset();
    std::string color(Color c);
    std::string background(Background bg);
    std::string style(Style s);

    std::string styled(const std::string& text, Color c);
    std::string styled(const std::string& text, Background bg);
    std::string styled(const std::string& text, Style s);
    std::string styled(const std::string& text, Color c, Style s);
    std::string styled(const std::string& text, Color c, Background bg);
    std::string styled(const std::string& text, Color c, Background bg, Style s);
}