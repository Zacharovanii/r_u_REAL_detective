#include "model/Location.h"

Location::Location(const MapTiles& data, const std::string& name, const std::string& filename)
    : tiles(data), name(name), filename(filename) {}

const MapTiles& Location::getTiles() const {
    return tiles;
}

const std::string& Location::getName() const {
    return name;
}

const std::string& Location::getFilename() const {
    return filename;
}

bool Location::isInside(size_t x, size_t y) const {
    if (y >= tiles.size()) return false;
    if (x >= tiles[y].size()) return false;
    return true;
}

bool Location::isWall(size_t x, size_t y) const {
    if (!isInside(x, y)) return true;
    return tiles[y][x] == '#';
}

void Location::addDoor(const Door& newDoor) {
    doors.emplace_back(newDoor);
}

Door* Location::getDoorAt(size_t x, size_t y) {
    for (auto& door : doors) {
        if (door.isIntersect(x, y)) {
            return &door;
        }
    }
    return nullptr;
}

const Door* Location::getDoorAt(size_t x, size_t y) const {
    for (const auto& door : doors) {
        if (door.isIntersect(x, y)) {
            return &door;
        }
    }
    return nullptr;
}

bool Location::hasDoorAt(size_t x, size_t y) const {
    return getDoorAt(x, y) != nullptr;
}

bool Location::canMoveTo(size_t x, size_t y) const {
    if (!isInside(x, y)) return false;
    if (isWall(x, y)) return false;
    
    // Проверяем, есть ли закрытая дверь
    const Door* door = getDoorAt(x, y);
    if (door && !door->isOpen()) return false;
    
    return true;
}