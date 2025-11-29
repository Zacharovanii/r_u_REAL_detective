#include "ui/MapRenderer.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include <iostream>

static constexpr std::string_view colorOf(char tile) {
    switch (tile) {

        // Пол
    case '.': return "\033[38;5;250m·\033[0m";        // Светлая точка пола
    case ',': return "\033[38;5;34m░\033[0m";         // Трава
    case '~': return "\033[38;5;39m≈\033[0m";         // Вода (не режет глаз)
    case ' ': return "\033[48;5;236m \033[0m";        // Тёмная плитка

        // Стены
    case '#': return "\033[38;5;245m█\033[0m";        // Стена каменная
    case '%': return "\033[38;5;130m▓\033[0m";        // Кирпичи
    case 'T': return "\033[38;5;28m♣\033[0m";         // Дерево

        // Персонажи
    case '@': return "\033[1;32m@\033[0m";            // Игрок
    case 'N': return "\033[1;36mN\033[0m";            // NPC

        // Предметы
    case 'I': return "\033[1;33m♦\033[0m";            // Предмет
    case 'C': return "\033[38;5;214m□\033[0m";        // Сундук
    case 'K': return "\033[1;33m⌑\033[0m";            // Ключ
    case 'P': return "\033[1;35m○\033[0m";            // Зелье

        // Архитектура
    case 'D': return "\033[38;5;166m╫\033[0m";        // Дверь
    case 'S': return "\033[1;37m↑\033[0m";            // Лестница
    case 'B': return "\033[38;5;97m╒╕\033[0m";         // Кровать
    case 'F': return "\033[38;5;208m▲\033[0m";        // Факел

        // Цветные зоны
    case 'X': return "\033[48;5;88m \033[0m";
    case 'O': return "\033[48;5;28m \033[0m";
    case 'L': return "\033[48;5;27m \033[0m";

        // Декор
    case 'M': return "\033[38;5;248m╱\033[0m";         // Паутина легкая

    default:  return "\033[38;5;196m?\033[0m";
    }
}


MapRenderer::MapRenderer(const Model& model) : model(model) { }

void MapRenderer::draw(int row, int col, int radiusY, int radiusX) const {
    int height = radiusY * 2 + 1;
    int width  = radiusX * 2 + 1;

    FrameDrawer::drawFrame(row, col, height + 2, width + 2, model.getCurrentLocationName());
    drawAreaAroundPlayer(row + 1, col + 1, radiusY, radiusX);
}

void MapRenderer::draw(int row, int col, int radius) const {
    draw(row, col, radius, radius);
}

void MapRenderer::drawAreaAroundPlayer(int row, int col,
                                      int radiusY, int radiusX) const {
    for (int dy = -radiusY; dy <= radiusY; dy++) {
        for (int dx = -radiusX; dx <= radiusX; dx++) {
            drawTile(row, col, radiusY, radiusX, dy, dx);
        }
    }
}

void MapRenderer::drawTile(int row,     int col,
                           int radiusY, int radiusX,
                           int dy,      int dx) const {
    const auto& map = model.getMap();
    const auto& p   = model.getPlayer();

    int checkY = static_cast<int>(p.y) + dy;
    int checkX = static_cast<int>(p.x) + dx;

    TerminalUtils::moveCursor(row + (dy + radiusY), col + (dx + radiusX));

    if (!isValidPosition(checkY, checkX)) {
        std::cout << " ";
        return;
    }

    auto y = static_cast<size_t>(checkY);
    auto x = static_cast<size_t>(checkX);

    if (y == p.y && x == p.x) {
        std::cout << colorOf('@');
        return;
    }

    std::cout << colorOf(map[y][x]);
}

bool MapRenderer::isValidPosition(int y, int x) const {
    return y >= 0 && x >= 0 &&
           y < static_cast<int>(model.getMapSizeY()) &&
           x < static_cast<int>(model.getMapSizeX(static_cast<size_t>(y)));
}