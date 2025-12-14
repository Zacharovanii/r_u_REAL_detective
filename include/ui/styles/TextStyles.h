#pragma once
#include <string>

enum class Color {
    Black = 0,
    Red = 1,

    ARROW = 14,
    Detective = 213,
    Grass = 64,
    Tree = 22,
    BrightTree = 100,
    HINT = 11,

    Sand = 94,

    Blue = 4,
    Magenta = 5,
    Cyan = 6,
    White = 7,

    BrightYellow = 11,
    BrightBlack = 8,
    BrightRed = 9,
    BrightBlue = 12,
    BrightMagenta = 13,
    BrightCyan = 14,
    BrightWhite = 15,

    Default = 256
};

enum class Background {
    Black = 0,

    Grass = 64,          // фон-трава
    Sand = static_cast<int>(Color::Sand),

    DarkGrass = 22,      // тёмная трава / лес
    LightGrass = 70,     // светлая трава

    BrightYellow = 11,
    Blue = 4,
    Magenta = 5,
    Cyan = 6,
    White = 7,

    Default = 256
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

struct StyledText {
    std::string text;
    Color color = Color::Default;
    Style style = Style::Reset;
    Background background = Background::Default;

    std::string getText() const;
    void setText(const std::string& newText);

    std::string getStyledText() const;

    void setColor(Color newColor);
    void setStyle(Style newStyle);
    void setBackground(Background newBackground);

    void resetStyles();
private:
    void append(std::string& result, std::string& value);
};