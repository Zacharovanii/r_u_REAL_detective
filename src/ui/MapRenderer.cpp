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
        s.setColor(Color::Green);
        break;

    case '~':
        s.setText("≈");
        s.setColor(Color::Cyan);
        break;

    case ' ':
        s.setText(" ");
        s.setBackground(Background::BrightBlack);
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
        s.setColor(Color::Green);
        break;

        // Персонажи
    case '@':
        s.setText("@");
        s.setColor(Color::BrightGreen);
        s.setStyle(Style::Bold);
        break;

    case 'N':
        s.setText("N");
        s.setColor(Color::BrightCyan);
        s.setStyle(Style::Bold);
        break;

        // Предметы
    case 'I':
        s.setText("♦");
        s.setColor(Color::BrightYellow);
        s.setStyle(Style::Bold);
        break;

        // Архитектура
    case 'D':
        s.setText("╫");
        s.setColor(Color::Yellow);
        break;

    case 'S':
        s.setText("↑");
        s.setColor(Color::BrightWhite);
        s.setStyle(Style::Bold);
        break;

        // Цветные зоны
    case 'X':
        s.setText(" ");
        s.setBackground(Background::Red);
        break;

    case 'O':
        s.setText(" ");
        s.setBackground(Background::Green);
        break;

    case 'L':
        s.setText(" ");
        s.setBackground(Background::Blue);
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