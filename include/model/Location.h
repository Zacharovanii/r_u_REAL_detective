#pragma once
#include <vector>
#include <string>
#include <memory>
#include <map>
#include "helpers/Types.h"
#include "objects/Door.h"
#include "objects/Interactable.h"

class Location {
private:
    MapTiles tiles;
    std::vector<std::unique_ptr<Interactable>> interactables;
    std::vector<Door> doors;
    std::string name;
    std::string filename;

    // Кэш для быстрого поиска интерактивных объектов по позиции
    mutable std::map<Position, Interactable*> interactable_cache;
    mutable bool cache_dirty = true;

    void rebuildCache() const;

public:
    Location() = default;
    Location(const MapTiles& data, const std::string& name, const std::string& filename);

    // Удаляем копирование (из-за unique_ptr)
    Location(const Location&) = delete;
    Location& operator=(const Location&) = delete;

    // Разрешаем перемещение
    Location(Location&&) = default;
    Location& operator=(Location&&) = default;

    [[nodiscard]] const MapTiles& getTiles() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getFilename() const;

    [[nodiscard]] bool isInside(size_t x, size_t y) const;
    [[nodiscard]] bool isWall(size_t x, size_t y) const;

    // --- Интерактивные объекты ---
    void addInteractable(std::unique_ptr<Interactable> interactable);
    [[nodiscard]] Interactable* getInteractableAt(size_t x, size_t y);
    [[nodiscard]] const Interactable* getInteractableAt(size_t x, size_t y) const;
    [[nodiscard]] bool hasInteractableAt(size_t x, size_t y) const;

    // --- Двери (специальный тип интерактивных объектов) ---
    void addDoor(const Door& newDoor);
    [[nodiscard]] Door* getDoorAt(size_t x, size_t y);
    [[nodiscard]] const Door* getDoorAt(size_t x, size_t y) const;
    [[nodiscard]] bool hasDoorAt(size_t x, size_t y) const;

    [[nodiscard]] bool canMoveTo(size_t x, size_t y) const;
    void interactAt(size_t x, size_t y);
};