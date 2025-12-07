#include "model/Location.h"
#include <algorithm>

Location::Location(
    MapTiles data,
    std::string name,
    std::string filename
    ) :
    tiles(std::move(data)),
    name(std::move(name)),
    filename(std::move(filename))
{}

const MapTiles& Location::getTiles() const { return tiles; }
const std::string& Location::getName() const { return name; }
const std::string& Location::getFilename() const { return filename; }

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


void Location::addInteractable(std::unique_ptr<Interactable> interactable) {
    interactables.push_back(std::move(interactable));
}

Interactable* Location::getInteractableAt(size_t x, size_t y) {
    for (auto& interactable : interactables) {
        if (interactable->isIntersect(x, y)) {
            return interactable.get();
        }
    }
    return nullptr;
}

const Interactable* Location::getInteractableAt(size_t x, size_t y) const {
    return const_cast<Location*>(this)->getInteractableAt(x, y);
}

bool Location::hasInteractableAt(size_t x, size_t y) const {
    return getInteractableAt(x, y) != nullptr;
}

void Location::interactAt(size_t x, size_t y) {
    if (auto* interactable = getInteractableAt(x, y)) {
        interactable->interact();
    }
}

bool Location::canMoveTo(size_t x, size_t y) const {
    if (!isInside(x, y) || isWall(x, y) || hasInteractableAt(x, y)) {
        return false;
    } else { return true; }
}