#include "model/Model.h"
#include "model/MapLoader.h"
#include <stdexcept>

Model::Model() {
    map = MapLoader::load("data/maps/hotel_1f.map");

    if (map.empty())
        throw std::runtime_error("Loaded map is empty!");

    // Игрок появляется в первой доступной точке (.)
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
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

void Model::moveUp() {
    if (player.y > 0 && map[player.y - 1][player.x] != '#')
        player.y--;
}

void Model::moveDown() {
    if (player.y < map.size() - 1 && map[player.y + 1][player.x] != '#')
        player.y++;
}

void Model::moveLeft() {
    if (player.x > 0 && map[player.y][player.x - 1] != '#')
        player.x--;
}

void Model::moveRight() {
    if (player.x < map[0].size() - 1 && map[player.y][player.x + 1] != '#')
        player.x++;
}
