#include "model/Model.h"
#include "model/MapLoader.h"
#include <stdexcept>
#include <iostream>

Model::Model() {
    initializeDoors();
    loadMap();
}


void Model::initializeDoors() {
    doors = {
        {"hotel_1f", {
            Door{
            {35, 5},
            "street",
            {1, 1},
            "Выйти на улицу"},
            Door{
            {28, 3},
            "hotel_2f",
            {23, 8},
            "Подняться на 2 этаж"}
        }},

        {"hotel_2f", {
            Door{
                {23, 7},
                "hotel_1f",
                {28, 4},
                "Спуститься на 1 этаж"},
        }},

        {"street", {
            Door{
            {1, 3},
            "hotel_1f",
            {34, 5},
            "Войти в отель"},
        }},

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

    auto it = doors.find(current_map);

    for (Door& door : it->second) {
        if (door.to_map == map_name) {
            player.x = door.to_pos.first;
            player.y = door.to_pos.second;

            current_map = map_name;
            return;
        }
    }
    player = {1, 1};
    current_map = map_name;
}

bool Model::tryTransition() {
    for (Door& door : doors[current_map]) {
        size_t door_x = door.from_pos.first;
        size_t door_y = door.from_pos.second;

        if (player.x == door_x && player.y == door_y) {
            loadMap(door.to_map);
            return true;
        }
    }
    return false;
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
