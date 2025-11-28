#include "model/Model.h"
#include "model/MapLoader.h"
#include <stdexcept>

Model::Model() {
    map = MapLoader::load("data/maps/hotel_1f.map");

    if (map.empty())
        throw std::runtime_error("Loaded map is empty!");

    // Игрок появляется в первой доступной точке (.)
    for (size_t y = 0; y < getMapSizeY(); y++) {
        for (size_t x = 0; x < getMapSizeX(y); x++) {
            if (map[y][x] == '.') {
                player = { x, y };
                return;
            }
        }
    }

    // Fallback
    player = { 1, 1 };
}

const Model::Player& Model::getPlayer() const {
    return player;
}

const std::vector<std::string>& Model::getMap() const {
    return map;
}

size_t Model::getMapSizeY() const {
    return map.size();
}

size_t Model::getMapSizeX() const {
    return map.empty() ? 0 : map[0].size();
}

size_t Model::getMapSizeX(size_t y) const {
    return y < map.size() ? map[y].size() : 0;
}

void Model::moveUp() {
    if (player.y > 0 && map[player.y - 1][player.x] != '#')
        player.y--;
}

void Model::moveDown() {
    if (player.y < getMapSizeY() - 1 && map[player.y + 1][player.x] != '#')
        player.y++;
}

void Model::moveLeft() {
    if (player.x > 0 && map[player.y][player.x - 1] != '#')
        player.x--;
}

void Model::moveRight() {
    if (player.x < getMapSizeX() - 1 && map[player.y][player.x + 1] != '#')
        player.x++;
}
