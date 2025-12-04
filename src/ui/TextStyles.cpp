#include "ui/styles/TextStyles.h"
#include <sstream>
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#endif

namespace TextStyles {
    
    // ==================== ИНИЦИАЛИЗАЦИЯ ====================
    
    void init() {
        #ifdef _WIN32
            Windows::initConsoleColors();
        #endif
    }
    
    void reset() {
        std::cout << "\033[0m";
        #ifdef _WIN32
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        #endif
    }
    
    // ==================== ОСНОВНЫЕ ФУНКЦИИ ====================
    
    std::string setColor(Color color) {
        std::ostringstream oss;
        int code = static_cast<int>(color);
        
        if (code <= 8) {
            // Обычные цвета
            oss << "\033[3" << code << "m";
        } else if (code <= 16) {
            // Яркие цвета
            oss << "\033[9" << (code - 8) << "m";
        } else if (code == 9) {
            // Цвет по умолчанию
            oss << "\033[39m";
        }
        
        #ifdef _WIN32
            // Для Windows дублируем через API
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            WORD attributes = Windows::colorToWindowsAttribute(color);
            SetConsoleTextAttribute(hConsole, attributes);
        #endif
        
        return oss.str();
    }
    
    std::string setBackground(Color color) {
        std::ostringstream oss;
        int code = static_cast<int>(color);
        
        if (code <= 8) {
            // Обычные цвета фона
            oss << "\033[4" << code << "m";
        } else if (code <= 16) {
            // Яркие цвета фона
            oss << "\033[10" << (code - 8) << "m";
        } else if (code == 9) {
            // Фон по умолчанию
            oss << "\033[49m";
        }
        
        return oss.str();
    }
    
    std::string setStyle(Style style) {
        std::ostringstream oss;
        oss << "\033[" << static_cast<int>(style) << "m";
        return oss.str();
    }
    
    std::string resetAll() {
        return "\033[0m";
    }
    
    // ==================== СТИЛИЗОВАННЫЕ СТРОКИ ====================
    
    std::string styled(const std::string& text, Color color, Style style) {
        std::ostringstream oss;
        oss << setColor(color) << setStyle(style) 
            << text << resetAll();
        return oss.str();
    }
    
    std::string styled(const std::string& text, Color color, 
                      Color backgroundColor, Style style) {
        std::ostringstream oss;
        oss << setColor(color) << setBackground(backgroundColor) 
            << setStyle(style) << text << resetAll();
        return oss.str();
    }
    
    // ==================== WINDOWS-СПЕЦИФИЧНЫЙ КОД ====================
    
    #ifdef _WIN32
    namespace Windows {
        
        void initConsoleColors() {
            // Включаем virtual terminal processing для поддержки ANSI escape codes
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD mode = 0;
            GetConsoleMode(hConsole, &mode);
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hConsole, mode);
        }
        
        WORD colorToWindowsAttribute(Color color, bool isBackground) {
            switch (color) {
                case Color::Black:        return isBackground ? 0 : 0;
                case Color::Red:          return isBackground ? BACKGROUND_RED : FOREGROUND_RED;
                case Color::Green:        return isBackground ? BACKGROUND_GREEN : FOREGROUND_GREEN;
                case Color::Yellow:       return isBackground ? BACKGROUND_RED | BACKGROUND_GREEN : FOREGROUND_RED | FOREGROUND_GREEN;
                case Color::Blue:         return isBackground ? BACKGROUND_BLUE : FOREGROUND_BLUE;
                case Color::Magenta:      return isBackground ? BACKGROUND_RED | BACKGROUND_BLUE : FOREGROUND_RED | FOREGROUND_BLUE;
                case Color::Cyan:         return isBackground ? BACKGROUND_GREEN | BACKGROUND_BLUE : FOREGROUND_GREEN | FOREGROUND_BLUE;
                case Color::White:        return isBackground ? BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE : FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
                case Color::BrightBlack:  return isBackground ? BACKGROUND_INTENSITY : FOREGROUND_INTENSITY;
                case Color::BrightRed:    return isBackground ? BACKGROUND_RED | BACKGROUND_INTENSITY : FOREGROUND_RED | FOREGROUND_INTENSITY;
                case Color::BrightGreen:  return isBackground ? BACKGROUND_GREEN | BACKGROUND_INTENSITY : FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                case Color::BrightYellow: return isBackground ? BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY : FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                case Color::BrightBlue:   return isBackground ? BACKGROUND_BLUE | BACKGROUND_INTENSITY : FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                case Color::BrightMagenta:return isBackground ? BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY : FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                case Color::BrightCyan:   return isBackground ? BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY : FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                case Color::BrightWhite:  return isBackground ? BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY : FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                default:                  return isBackground ? 0 : FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            }
        }
        
    } // namespace Windows
    #endif
    
} // namespace TextStyles