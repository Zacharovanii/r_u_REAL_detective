#include "ui/MapRenderer.h"
#include "ui/TerminalUtils.h"
#include "ui/FrameDrawer.h"
#include "ui/styles/TextStyles.h"
#include <iostream>

static StyledText colorOf(char tile) {
    StyledText s;
    switch (tile) {
        // Пол
    case '.':
        s.setText("·");
        s.setColor(Color::BrightBlack);
        break;

    case ',':
        s.setText("░");
        s.setColor(Color::Grass);
        break;

    case '~':
        s.setText("≈");
        s.setColor(Color::Cyan);
        break;

        // Стены
    case '#':
        s.setText("█");
        s.setColor(Color::BrightBlack);
        break;

    case '%':
        s.setText("▓");
        s.setColor(Color::Red);
        break;

    case 'T':
        s.setText("♣");
        s.setColor(Color::BrightTree);
        s.setBackground(Background::DarkGrass);
        break;

        // Персонажи
    case '@':
        s.setText("@");
        s.setColor(Color::Detective);
        s.setStyle(Style::Bold);
        break;

    case 'N':
        s.setText("N");
        s.setColor(Color::BrightCyan);
        s.setStyle(Style::Bold);
        break;

        // Предметы
    case 'C':
        s.setText("♦");
        s.setColor(Color::HINT);
        s.setStyle(Style::Bold);
        s.setBackground(Background::Sand);
        break;

        // Архитектура
    case 'D':
        s.setText("╫");
        s.setColor(Color::Red);
        break;

    case 'w': // Лестница/выход наверх
        s.setText("↑");
        s.setColor(Color::ARROW);
        s.setStyle(Style::Bold);
        s.setBackground(Background::Sand);
        break;

    case 's': // Лестница/выход вниз
        s.setText("↓");
        s.setColor(Color::ARROW);
        s.setStyle(Style::Bold);
        s.setBackground(Background::Sand);
        break;

    case 'a': // Выход налево
        s.setText("←");
        s.setColor(Color::ARROW);
        s.setStyle(Style::Bold);
        s.setBackground(Background::Sand);
        break;

    case 'd': // Выход направо
        s.setText("→");
        s.setColor(Color::ARROW);
        s.setStyle(Style::Bold);
        s.setBackground(Background::Sand);
        break;

        // Цветные зоны
    case 'x':
        s.setText("█");
        s.setColor(Color::Sand);
        s.setBackground(Background::Sand);
        break;


    default:
        s.setText(std::string(1, tile));
        s.setColor(Color::BrightRed);
        break;
    }
    return s;
}

MapRenderer::MapRenderer(Model& model) : model(model) { }

void MapRenderer::draw(const PanelMetrics& pm, int radiusY, int radiusX) const {
    FrameDrawer::drawFrameWithTitle(pm, model.getCurrentLocationName());
    drawAreaAroundPlayer(pm, radiusY, radiusX);
}

void MapRenderer::drawAreaAroundPlayer(const PanelMetrics& pm, int radiusY, int radiusX) const {
    for (int dy = -radiusY; dy <= radiusY; dy++) {
        for (int dx = -radiusX; dx <= radiusX; dx++) {
            TerminalUtils::moveCursor(pm.row + (dy + radiusY) + 1, pm.col + (dx + radiusX) + 1);
            drawTile(dy, dx);
        }
    }
}

void MapRenderer::drawTile(int dy, int dx) const {
    Location* location = model.getCurrentLocation();
    if (!location) return;

    const auto& p = model.getPlayer();
    const auto& tiles = location->getTiles();

    int checkY = static_cast<int>(p.getY()) + dy;
    int checkX = static_cast<int>(p.getX()) + dx;

    if (!isValidPosition(checkY, checkX)) {
        std::cout << " ";
        return;
    }

    auto y = static_cast<size_t>(checkY);
    auto x = static_cast<size_t>(checkX);

    StyledText baseTile = colorOf(tiles[y][x]);

    if (y == p.getY() && x == p.getX()) {
        StyledText player = colorOf('@');

        if (baseTile.background != Background::Default)
            player.setBackground(baseTile.background);

        std::cout << player.getStyledText();
        return;
    }
    if (auto* door = location->getDoorAt({x, y})) {
        if (door->isOpen()) {
            std::cout << baseTile.getStyledText();
        } else {
            std::cout << colorOf('#').getStyledText();
        }
        return;
    }
    std::cout << baseTile.getStyledText();
}

bool MapRenderer::isValidPosition(int y, int x) const {
    const Location* location = model.getCurrentLocation();
    if (!location) return false;

    return y >= 0 && x >= 0 &&
           y < static_cast<int>(location->getTiles().size()) &&
           x < static_cast<int>(location->getTiles()[static_cast<size_t>(y)].size());
}