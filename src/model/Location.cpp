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

void Location::addDoor(const Door& newDoor) { doors.push_back(newDoor); }
void Location::addInteractable(std::unique_ptr<Interactable> interactable) {
    interactables.push_back(std::move(interactable));
}

Door* Location::getDoorAt(Position pos) {
    for (auto& door : doors) {
        if (door.isTriggered(pos))
            return &door;
    }
    return nullptr;
}

Interactable* Location::getInteractableAt(Position pos) const {
    for (auto& interactable : interactables) {
        if (interactable->isIntersect(pos))
            return interactable.get();
    }
    return nullptr;
}

bool Location::canMoveTo(size_t x, size_t y) const {
    if (y >= tiles.size() || x >= tiles[y].size() || tiles[y][x] == '#') {
        // Вне карты или стена
        return false;
    }
    else {
        // Проверяем интерактивные объекты
        for (auto& interactable : interactables) {
            if (interactable->isIntersect(x, y))
                return false;
        }
        return true;
    }
}