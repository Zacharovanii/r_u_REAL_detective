#include "model/Model.h"
#include "model/MapLoader.h"
#include <stdexcept>
#include <iostream>

Model::Model() {
    initializeDoors();
    loadMap();  // Используем понятные имена
}


void Model::initializeDoors() {
    doors = {
        // Отель -> Улица
        {"hotel_1f", {33, 5, "street", 1, 1, "Выйти на улицу"}},
        // Улица -> Отель
        {"street", {1, 3, "hotel_1f", 34, 5, "Войти в отель"}},
        // Улица -> Полиция
        // {"street", 15, 8, "police_station", 2, 1, "Полицейский участок"},
        // Полиция -> Улица
        // {"police_station", 2, 1, "street", 15, 8, "Выйти на улицу"}
    };
}

void Model::loadMap() {
    std::string filename = "data/maps/" + current_map + ".map";
    map = MapLoader::load(filename);

    if (map.empty()) {
        throw std::runtime_error("Loaded map is empty: " + filename);
    }

    player = {1, 1};
}

void Model::loadMap(const std::string& map_name) {
    std::string filename = "data/maps/" + map_name + ".map";
    map = MapLoader::load(filename);

    if (map.empty()) {
        throw std::runtime_error("Loaded map is empty: " + filename);
    }

    // Устанавливаем позицию игрока
    auto it = doors.find(current_map);
    if (!doors.empty()) {
        player.x = it->second.to_x;
        player.y = it->second.to_y;
    } else {
        player = {1, 1};  // Ultimate fallback
    }

    current_map = map_name;
}

bool Model::tryTransition() {
    size_t door_x = doors[current_map].door_x;
    size_t door_y = doors[current_map].door_y;

    if (player.x == door_x && player.y == door_y) {
        loadMap(doors[current_map].to_map);
        return true;
    } else {
        return false;
    }
}

const std::string& Model::getCurrentMap() const {
    return current_map;
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
