#include "model/Model.h"
#include "helpers/MapLoader.h"
#include "helpers/GameInitializer.h"

Model::Model() : player(1, 1){
    GameInitializer::initGameWorld(game_map);
    GameInitializer::loadStartLocation(game_map, player, "hotel_1f");
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
    return game_map.getCurrentLocationName();
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