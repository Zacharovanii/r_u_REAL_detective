#pragma once
#include <vector>
#include <string>
#include <memory>
#include "helpers/Types.h"
#include "objects/Door.h"
#include "objects/Interactable.h"

class Location {
private:
    std::vector<std::unique_ptr<Interactable>> interactables;
    std::vector<Door> doors;
    MapTiles tiles;
    std::string name;

public:
    Location() = default;
    Location(MapTiles data, std::string name);

    // Удаляем копирование (из-за unique_ptr)
    Location(const Location&) = delete;
    Location& operator=(const Location&) = delete;

    // Разрешаем перемещение
    Location(Location&&) = default;
    Location& operator=(Location&&) = default;

    [[nodiscard]] const MapTiles& getTiles() const;
    [[nodiscard]] const std::string& getName() const;

    [[nodiscard]] bool isInside(size_t x, size_t y) const;
    [[nodiscard]] bool isWall(size_t x, size_t y) const;

    void addInteractable(std::unique_ptr<Interactable> interactable);
    [[nodiscard]] Interactable* getInteractableAt(Position pos) const;
    [[nodiscard]] bool hasInteractableAt(size_t x, size_t y) const;

    void addDoor(const Door& newDoor);
    [[nodiscard]] Door* getDoorAt(Position pos);

    [[nodiscard]] bool canMoveTo(size_t x, size_t y) const;
};