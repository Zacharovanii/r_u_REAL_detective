#pragma once
#include <unordered_map>
#include <string>
#include "Location.h"

class Map {
private:
    std::unordered_map<std::string, Location> locations;
    std::string current_location;

public:
    Map() = default;

    void addLocation(const std::string& name, Location location);
    void setCurrentLocation(const std::string& location_name);

    [[nodiscard]] Location* getCurrentLocation();
    [[nodiscard]] const Location* getCurrentLocation() const;
    [[nodiscard]] Location* getLocation(const std::string& name);
    [[nodiscard]] const std::string& getCurrentLocationName() const;

    bool changeLocation(const std::string& new_location);

    void interactAt(size_t x, size_t y);
    void triggerDoorAt(Player& player, size_t x, size_t y);
};