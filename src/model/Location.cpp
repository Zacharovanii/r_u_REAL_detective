#include "model/Location.h"
#include <algorithm>


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

// bool Location::canMoveTo(size_t x, size_t y) const {
//     if (!isInside(x, y)) return false;
//     if (isWall(x, y)) return false;
//
//     // Проверяем, есть ли закрытая дверь
//     const Door* door = getDoorAt(x, y);
//     if (door && !door->isOpen()) return false;
//
//     return true;
// }

void Location::rebuildCache() const {
    if (!cache_dirty) return;

    interactable_cache.clear();
    for (const auto& interactable : interactables) {
        interactable_cache[interactable->getPosition()] = interactable.get();
    }
    cache_dirty = false;
}

void Location::addInteractable(std::unique_ptr<Interactable> interactable) {
    interactables.push_back(std::move(interactable));
    cache_dirty = true;
}

Interactable* Location::getInteractableAt(size_t x, size_t y) {
    rebuildCache();
    auto it = interactable_cache.find({x, y});
    return it != interactable_cache.end() ? it->second : nullptr;
}

const Interactable* Location::getInteractableAt(size_t x, size_t y) const {
    // rebuildCache();
    // auto it = interactable_cache.find({x, y});
    // return it != interactable_cache.end() ? it->second : nullptr;

    return const_cast<Location*>(this)->getInteractableAt(x, y);
}

bool Location::hasInteractableAt(size_t x, size_t y) const {
    return getInteractableAt(x, y) != nullptr;
}

void Location::interactAt(Player& player, size_t x, size_t y) {
    if (auto* interactable = getInteractableAt(x, y)) {
        interactable->interact(player);
    }
}

// Обновляем canMoveTo чтобы учитывать интерактивные объекты
bool Location::canMoveTo(size_t x, size_t y) const {
    if (!isInside(x, y) || isWall(x, y)) {
        return false;
    }

    // Проверяем, есть ли непроходимый интерактивный объект
    // if (const auto* interactable = getInteractableAt(x, y)) {
    //     // Можно добавить логику проверки проходимости
    //     // Например, если объект блокирует движение
    //     return true; // временно разрешаем движение
    // }

    return true;
}