#include "model/Model.h"
#include "model/MapLoader.h"

Model::Model() : player(1, 1){
    initializeGameWorld();
    loadInitialLocation();
}

void Model::initializeGameWorld() {
    // Создаем и настраиваем локации
    Location hotel_1f(MapLoader::loadByName("hotel_1f"), "Hotel First Floor", "hotel_1f");
    Location hotel_2f(MapLoader::loadByName("hotel_2f"), "Hotel Second Floor", "hotel_2f");
    Location street(MapLoader::loadByName("street"), "Street", "street");

    // Добавляем двери в локации
    // Пример: дверь с 1 этажа на 2 этаж
    hotel_1f.addDoor(Door(
        Position{28, 3},
        "Stairs to 2F",
        "A staircase leading to the second floor",
        "hotel_2f",
        Position{23, 8},  // позиция появления на 2 этаже
        true
    ));

    // Пример: дверь со 2 этажа на 1 этаж
    hotel_2f.addDoor(Door(
        Position{23, 7},
        "Stairs to 1F",
        "A staircase leading to the first floor",
        "hotel_1f",
        Position{28, 4},  // позиция появления на 1 этаже
        true
    ));

    // Пример: входная дверь
    hotel_1f.addDoor(Door(
        Position{35, 5},
        "Main Entrance",
        "The main entrance to the hotel",
        "street",
        Position{1, 1},
        true
    ));

    street.addDoor(Door(
        Position{1, 3},
        "Hotel Entrance",
        "The entrance to the hotel",
        "hotel_1f",
        Position{34, 5},
        true
    ));

    // Добавляем локации в карту
    game_map.addLocation("hotel_1f", hotel_1f);
    game_map.addLocation("hotel_2f", hotel_2f);
    game_map.addLocation("street", street);
}

void Model::loadInitialLocation() {
    current_location_name = "hotel_1f";
    game_map.setCurrentLocation(current_location_name);
    player.setPositionAt(1, 1);
}

const Player& Model::getPlayer() const {
    return player;
}

const Map& Model::getMap() const {
    return game_map;
}

const Location* Model::getCurrentLocation() const {
    return game_map.getCurrentLocation();
}

const std::string& Model::getCurrentLocationName() const {
    return current_location_name;
}

void Model::moveUp() {
    const Location* location = getCurrentLocation();
    if (!location) return;

    size_t new_x = player.getX();
    size_t new_y = player.getY() - 1;

    if (location->canMoveTo(new_x, new_y)) {
        player.setPositionAt(new_x, new_y);
    }
}

void Model::moveDown() {
    const Location* location = getCurrentLocation();
    if (!location) return;

    size_t new_x = player.getX();
    size_t new_y = player.getY() + 1;

    if (location->canMoveTo(new_x, new_y)) {
        player.setPositionAt(new_x, new_y);
    }
}

void Model::moveLeft() {
    const Location* location = getCurrentLocation();
    if (!location) return;

    size_t new_x = player.getX() - 1;
    size_t new_y = player.getY();

    if (location->canMoveTo(new_x, new_y)) {
        player.setPositionAt(new_x, new_y);
    }
}

void Model::moveRight() {
    const Location* location = getCurrentLocation();
    if (!location) return;

    size_t new_x = player.getX() + 1;
    size_t new_y = player.getY();

    if (location->canMoveTo(new_x, new_y)) {
        player.setPositionAt(new_x, new_y);
    }
}

void Model::interact() {
    game_map.interactWithDoorAt(player, player.getX(), player.getY());

    // Обновляем текущее имя локации после возможного перехода
    current_location_name = game_map.getCurrentLocationName();
}

// Утилиты для отображения (можно оставить для совместимости)
size_t Model::getMapSizeY() const {
    const Location* location = getCurrentLocation();
    if (!location) return 0;

    const auto& tiles = location->getTiles();
    return tiles.size();
}

size_t Model::getMapSizeX() const {
    const Location* location = getCurrentLocation();
    if (!location) return 0;

    const auto& tiles = location->getTiles();
    return tiles.empty() ? 0 : tiles[0].size();
}

size_t Model::getMapSizeX(size_t y) const {
    const Location* location = getCurrentLocation();
    if (!location) return 0;

    const auto& tiles = location->getTiles();
    return y < tiles.size() ? tiles[y].size() : 0;
}