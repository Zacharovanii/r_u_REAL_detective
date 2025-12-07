#include "ui/styles/TextStyles.h"
#include <string>

namespace TextStyles {
    std::string reset() {return "\033[0m";}

    std::string color(Color c) {
        return "\033[" + std::to_string(static_cast<int>(c)) + "m";
    }
    std::string background(Background bg) {
        return "\033[" + std::to_string(static_cast<int>(bg)) + "m";
    }
    std::string style(Style s) {
        return "\033[" + std::to_string(static_cast<int>(s)) + "m";
    }

    // Комбинированные функции
    std::string styled(const std::string& text, Color c) { return color(c) + text + reset(); }
    std::string styled(const std::string& text, Background bg) { return background(bg) + text + reset(); }
    std::string styled(const std::string& text, Style s) { return style(s) + text + reset(); }
    std::string styled(const std::string& text, Color c, Background bg) { return color(c) + background(bg) + text + reset(); }
    std::string styled(const std::string& text, Color c, Style s) { return color(c) + style(s) + text + reset(); }
    std::string styled(const std::string& text, Color c, Background bg, Style s) { return color(c) + background(bg) + style(s) + text + reset(); }
}