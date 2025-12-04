#pragma once
#include <string>
#include <ostream>

#ifdef _WIN32
    #include <windows.h>
#endif

namespace TextStyles {
    // Базовые цвета ANSI
    enum class Color {
        Black = 0,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
        BrightBlack,
        BrightRed,
        BrightGreen,
        BrightYellow,
        BrightBlue,
        BrightMagenta,
        BrightCyan,
        BrightWhite,
        Default = 9
    };
    
    // Стили текста
    enum class Style {
        Normal = 0,
        Bold = 1,
        Dim = 2,
        Italic = 3,
        Underline = 4,
        Blink = 5,
        Reverse = 7,
        Hidden = 8
    };
    
    // Предопределённые темы для элементов UI
    namespace Theme {
        constexpr Color Title = Color::BrightCyan;
        constexpr Color DialogueSpeaker = Color::BrightYellow;
        constexpr Color Important = Color::BrightRed;
        constexpr Color Hint = Color::BrightGreen;
        constexpr Color NormalText = Color::White;
        constexpr Color Number = Color::BrightMagenta;
        constexpr Color Interactive = Color::BrightBlue;
        constexpr Color Description = Color::BrightBlack;
        constexpr Color Emoji = Color::Yellow;
    }
    
    // Инициализация системы цветов
    void init();
    
    // Восстановление дефолтных настроек
    void reset();
    
    // Установка цвета текста
    std::string setColor(Color color);
    
    // Установка цвета фона
    std::string setBackground(Color color);
    
    // Установка стиля текста
    std::string setStyle(Style style);
    
    // Сброс всех стилей к дефолтным
    std::string resetAll();
    
    // Создание стилизованной строки
    std::string styled(const std::string& text, Color color, 
                      Style style = Style::Normal);
    
    // Создание строки с несколькими стилями
    std::string styled(const std::string& text, 
                      Color color, 
                      Color backgroundColor, 
                      Style style = Style::Normal);
    
    // Для Windows - дополнительные утилиты
    #ifdef _WIN32
    namespace Windows {
        void initConsoleColors();
        WORD colorToWindowsAttribute(Color color, bool isBackground = false);
    }
    #endif
}