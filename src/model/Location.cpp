#include "model/Location.h"
#include <algorithm>

Location::Location(
    MapTiles data,
    std::string name
    ) :
    tiles(std::move(data)),
    name(std::move(name))
{}

const MapTiles& Location::getTiles() const { return tiles; }
const std::string& Location::getName() const { return name; }

bool Location::isInside(size_t x, size_t y) const {
    if (y >= tiles.size() || x >= tiles[y].size())
        return false;
    else
        return true;
}

bool Location::isWall(size_t x, size_t y) const {
    if (!isInside(x, y)) return true;
    return tiles[y][x] == '#';
}

void Location::addDoor(const Door& newDoor) {
    doors.emplace_back(newDoor);
}

Door* Location::getDoorAt(Position pos) {
    for (auto& door : doors) {
        if (door.isIntersect(pos)) {
            return &door;
        }
    }
    return nullptr;
}

void Location::addInteractable(std::unique_ptr<Interactable> interactable) {
    interactables.push_back(std::move(interactable));
}

Interactable* Location::getInteractableAt(Position pos) const {
    for (auto& interactable : interactables) {
        if (interactable->isIntersect(pos)) {
            return interactable.get();
        }
    }
    return nullptr;
}


bool Location::hasInteractableAt(size_t x, size_t y) const {
    for (auto& interactable : interactables) {
        if (interactable->isIntersect(x, y)) {
            return true;
        }
    }
    return false;
}

bool Location::canMoveTo(size_t x, size_t y) const {
    if (!isInside(x, y) || isWall(x, y) || hasInteractableAt(x, y)) {
        return false;
    } else { return true; }
}