#include <sstream>
#include "helpers/TextWrapper.h"

int TextWrapper::getStringWidth(const std::string& str) {
    int width = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = str[i];

        // Определяем длину символа в UTF-8
        size_t charLen = 1;
        if ((c & 0x80) == 0x00) {          // 0xxxxxxx (ASCII)
            charLen = 1;
        } else if ((c & 0xE0) == 0xC0) {   // 110xxxxx (2 байта)
            charLen = 2;
        } else if ((c & 0xF0) == 0xE0) {   // 1110xxxx (3 байта)
            charLen = 3;
        } else if ((c & 0xF8) == 0xF0) {   // 11110xxx (4 байта)
            charLen = 4;
        }

        // Все символы считаем шириной 1 (упрощённо)
        width += 1;
        i += charLen;
    }
    return width;
}

std::vector<std::string> TextWrapper::wrap(const std::string& text, int max_width) {
    std::vector<std::string> lines;
    std::string current_line;
    int current_width = 0;

    size_t pos = 0;
    while (pos < text.length()) {
        // Находим следующее слово
        size_t word_start = text.find_first_not_of(' ', pos);
        if (word_start == std::string::npos) break;

        size_t word_end = text.find_first_of(' ', word_start);
        if (word_end == std::string::npos) word_end = text.length();

        std::string word = text.substr(word_start, word_end - word_start);
        int word_width = getStringWidth(word);

        // Обработка слишком длинных слов
        if (word_width > max_width) {
            if (!current_line.empty()) {
                lines.push_back(current_line);
                current_line.clear();
                current_width = 0;
            }

            // Разбиваем длинное слово посимвольно
            for (char c : word) {
                std::string single_char(1, c);
                int char_width = getStringWidth(single_char);

                if (current_width + char_width > max_width) {
                    lines.push_back(current_line);
                    current_line = single_char;
                    current_width = char_width;
                } else {
                    current_line += single_char;
                    current_width += char_width;
                }
            }
        }
        // Обычное слово
        else {
            if (current_line.empty()) {
                current_line = word;
                current_width = word_width;
            } else if (current_width + 1 + word_width <= max_width) {
                current_line += ' ' + word;
                current_width += 1 + word_width;
            } else {
                lines.push_back(current_line);
                current_line = word;
                current_width = word_width;
            }
        }

        pos = word_end;
    }

    if (!current_line.empty()) {
        lines.push_back(current_line);
    }

    return lines;
}