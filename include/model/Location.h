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
public:
    Location() = default;
    explicit Location(MapTiles data);

    [[nodiscard]] const MapTiles& getTiles() const;

    void addInteractable(std::unique_ptr<Interactable> interactable);
    void addDoor(const Door& newDoor);

    [[nodiscard]] Interactable* getInteractableAt(Position pos) const;
    [[nodiscard]] Door* getDoorAt(Position pos);

    [[nodiscard]] bool canMoveTo(size_t x, size_t y) const;
};