#include "model/Location.h"
#include <algorithm>

Location::Location(
    MapTiles data
    ) :
    tiles(std::move(data))
{}

const MapTiles& Location::getTiles() const { return tiles; }

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
    if ( y >= tiles.size() || x >= tiles[y].size() ||
        tiles[y][x] == '#' || tiles[y][x] == 'T' ||
        tiles[y][x] == '%' || tiles[y][x] == '~' ||
        tiles[y][x] == 'J' || tiles[y][x] == 'H'
        ) {
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