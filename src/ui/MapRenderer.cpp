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


MapRenderer::MapRenderer(Model& model) : model(model) { }

void MapRenderer::draw(int row, int col, int radiusY, int radiusX) const {
    int height = radiusY * 2 + 1;
    int width  = radiusX * 2 + 1;

    PanelMetrics pm = {static_cast<size_t>(row), static_cast<size_t>(col), static_cast<size_t>(height + 2), static_cast<size_t>(width + 2)};
    FrameDrawer::drawFrameWithTitle(pm, model.getCurrentLocationName());
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
    Location* location = model.getCurrentLocation();
    if (!location) return;

    const auto& p = model.getPlayer();
    const auto& tiles = location->getTiles();

    int checkY = static_cast<int>(p.getY()) + dy;
    int checkX = static_cast<int>(p.getX()) + dx;

    TerminalUtils::moveCursor(row + (dy + radiusY), col + (dx + radiusX));

    if (!isValidPosition(checkY, checkX)) {
        std::cout << " ";
        return;
    }

    auto y = static_cast<size_t>(checkY);
    auto x = static_cast<size_t>(checkX);

    // Рисуем игрока
    if (y == p.getY() && x == p.getX()) {
        std::cout << colorOf('@');
        return;
    }

    if (auto* door = location->getDoorAt({x, y})) {
        if (door->isOpen()) {
            std::cout << colorOf('D');
        } else {
            std::cout << colorOf('#');
        }
        return;
    }

    // Рисуем обычный тайл
    std::cout << colorOf(tiles[y][x]);
}

bool MapRenderer::isValidPosition(int y, int x) const {
    const Location* location = model.getCurrentLocation();
    if (!location) return false;

    return y >= 0 && x >= 0 &&
           y < static_cast<int>(location->getTiles().size()) &&
           x < static_cast<int>(location->getTiles()[static_cast<size_t>(y)].size());
}