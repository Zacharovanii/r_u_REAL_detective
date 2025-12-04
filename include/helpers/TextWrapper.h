#pragma once
#include <string>
#include <vector>

class TextWrapper {
public:
    static int getStringWidth(const std::string& str);
    static std::vector<std::string> wrap(const std::string& text, int max_width);
};