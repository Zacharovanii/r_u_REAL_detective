#pragma once
#include <vector>
#include <string>
#include "Types.h"
#include "Door.h"


class Location {
private:
    MapTiles tiles;
    std::vector<Door> doors;
    std::string name;
    std::string filename;

public:
    Location() = default;
    Location(const MapTiles& data, const std::string& name, const std::string& filename);

    [[nodiscard]] const MapTiles& getTiles() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getFilename() const;

    [[nodiscard]] bool isInside(size_t x, size_t y) const;
    [[nodiscard]] bool isWall(size_t x, size_t y) const;

    // --- двери ---
    void addDoor(const Door& newDoor);
    [[nodiscard]] Door* getDoorAt(size_t x, size_t y);
    [[nodiscard]] const Door* getDoorAt(size_t x, size_t y) const;
    [[nodiscard]] bool hasDoorAt(size_t x, size_t y) const;

    // --- для движения ---
    [[nodiscard]] bool canMoveTo(size_t x, size_t y) const;
};